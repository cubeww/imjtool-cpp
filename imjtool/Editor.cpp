#include "Editor.h"

#include "Game.h"
#include "Object.h"

inline float pointdir(float x1, float y1, float x2, float y2)
{
	return atan((y1 - y2) / (x1 - x2));
}

inline float pointdist(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

Editor::Editor()
{
}

void Editor::update()
{
	auto mousePos = GetMousePos();
	auto windowPos = GetWindowPos();
	auto windowSize = GetWindowSize();
	auto cursorStartPos = GetCursorStartPos();
	auto mouseInPos = ImVec2(mousePos.x - windowPos.x - cursorStartPos.x, mousePos.y - windowPos.y - cursorStartPos.y);

	mouseInTitle = sf::FloatRect(windowPos.x, windowPos.y, windowSize.x, cursorStartPos.y).contains(mousePos.x, mousePos.y);
	auto cursorInArea = sf::FloatRect(0, 0, 799, 607).contains(mouseInPos.x, mouseInPos.y);

	auto leftPress = IsMouseClicked(ImGuiMouseButton_Left);
	auto leftHold = IsMouseDown(ImGuiMouseButton_Left);
	auto leftRelease = IsMouseReleased(ImGuiMouseButton_Left);

	auto rightPress = IsMouseClicked(ImGuiMouseButton_Right);
	auto rightHold = IsMouseDown(ImGuiMouseButton_Right);
	auto rightRelease = IsMouseReleased(ImGuiMouseButton_Right);

	auto dragHold = InputMgr.isKeyHold(sf::Keyboard::Space);
	auto pickerHold = InputMgr.isKeyHold(sf::Keyboard::LControl);
	auto codeHold = InputMgr.isKeyHold(sf::Keyboard::LAlt);

	auto snappedPos = ImVec2(floor(mouseInPos.x / snap.x) * snap.x, floor(mouseInPos.y / snap.y) * snap.y);
	auto focused = IsWindowFocused();

	if (cursorInArea)
	{
		if (dragHold && focused)
		{
			if (leftHold)
			{
				if (caughtObject == nullptr)
				{
					for (auto const& i : ObjMgr.objects)
					{
						auto col = ObjMgr.collisionPoint(mouseInPos.x, mouseInPos.y, i->index);
						if (col != nullptr)
						{
							caughtObject = col;
							caughtOldPos = ImVec2(col->x, col->y);
							break;
						}
					}
				}
				else
				{
					caughtObject->x = snappedPos.x;
					caughtObject->y = snappedPos.y;
				}
			}
			if (leftRelease)
			{
				finishMoveObject();
			}
		}
		else if (pickerHold && focused)
		{
			if (leftPress)
			{
				auto col = ObjMgr.collisionPointList(mouseInPos.x, mouseInPos.y, ALL);
				for (auto const& i : col)
				{
					selectSprite = i->sprite;
					selectIndex = i->index;
				}
			}
		}
		else if (codeHold && focused)
		{
			// TODO: Code Edit
		}
		else
		{
			if (leftHold && focused)
			{
				if (leftHoldLast)
				{
					auto dir = pointdir(mouseLastPos.x, mouseLastPos.y, mouseInPos.x, mouseInPos.y);
					auto n = floor(pointdist(mouseLastPos.x, mouseLastPos.y, mouseInPos.x, mouseInPos.y));
					auto len = 1;
					auto dx = len * cos(dir);
					auto dy = len * sin(dir);
					auto xx = mouseLastPos.x;
					auto yy = mouseLastPos.y;
					auto xxnLast = -1;
					auto yynLast = -1;
					for (auto i = 0; i < n; i++)
					{
						auto xxn = floor(xx / snap.x) * snap.x;
						auto yyn = floor(yy / snap.y) * snap.y;
						if (xxn != xxnLast || yyn != yynLast) {
							xxnLast = xxn;
							yynLast = yyn;
							finishCreateObject(xxn, yyn);
						}
						xx += dx;
						yy += dy;
					}
				}
				finishCreateObject(snappedPos.x, snappedPos.y);
			}
			else if (rightHold)
			{
				vector<shared_ptr<Object>> col;
				if (rightHoldLast)
				{
					col = ObjMgr.collisionLineList(mouseLastPos.x, mouseLastPos.y, mouseInPos.x, mouseInPos.y, ALL);
				}
				else
				{
					col = ObjMgr.collisionPointList(mouseInPos.x, mouseInPos.y, ALL);
				}
				for (auto const& i : col)
				{
					if (i->index == GetIndex(PlayerStart) || i->index == GetIndex(Player))
					{
						continue;
					}
					addRemoveEvent(i->x, i->y, i->index);
					Destroy(i);
				}
			}
		}
		if (!dragHold)
		{
			finishMoveObject();
		}
		if (leftRelease || rightRelease)
		{
			finishEvent();
		}
	}
	else
	{
		// TODO
	}

	mouseLastPos.x = mouseInPos.x;
	mouseLastPos.y = mouseInPos.y;
	leftHoldLast = leftHold;
	rightHoldLast = rightHold;

	if (cursorInArea)
	{
		// draw
		SetCursorPos(ImVec2(snappedPos.x + cursorStartPos.x, snappedPos.y + cursorStartPos.y));
		auto spr = selectSprite->items[0]->sprite;
		Image(*spr, sf::Color(255, 255, 255, 100));
	}

	// undo & redo
	if (InputMgr.isKeyHold(sf::Keyboard::LControl) && InputMgr.isKeyPress(sf::Keyboard::Z))
	{
		undo();
	}
	if (InputMgr.isKeyHold(sf::Keyboard::LControl) && InputMgr.isKeyPress(sf::Keyboard::Y))
	{
		redo();
	}
}

void Editor::addCreateEvent(float x, float y, int objectIndex)
{
	if (curEvent == nullptr)
	{
		curEvent = make_shared<UndoEvent>(Create);
	}
	curEvent->addSubEvent(SubEvent(x, y, objectIndex));
}

void Editor::addRemoveEvent(float x, float y, int objectIndex)
{
	if (curEvent == nullptr)
	{
		curEvent = make_shared<UndoEvent>(Remove);
	}
	curEvent->addSubEvent(SubEvent(x, y, objectIndex));
}

void Editor::addMoveEvent(shared_ptr<Object> object, float oldX, float oldY, float newX, float newY)
{
	if (curEvent == nullptr)
	{
		curEvent = make_shared<UndoEvent>(Move);
	}
	curEvent->addSubEvent(SubEvent(object->index, oldX, oldY, newX, newY));
}

void Editor::finishEvent()
{
	if (curEvent != nullptr)
	{
		// clean useless events
		auto size = undoEvents.size();
		for (auto i = undoPos; i < size; i++)
		{
			undoEvents.erase(undoEvents.begin() + undoPos);
		}
		undoEvents.push_back(curEvent);
		curEvent = nullptr;
		undoPos++;
	}
}

void Editor::finishCreateObject(float x, float y)
{
	if (ObjMgr.atPosition(x, y, selectIndex).empty())
	{
		auto inst = CreateByIndex(selectIndex, x, y);
		addCreateEvent(inst->x, inst->y, inst->index);
	}
}

void Editor::finishMoveObject()
{
	if (caughtObject != nullptr)
	{
		addMoveEvent(caughtObject, caughtOldPos.x, caughtOldPos.y, caughtObject->x, caughtObject->y);
		caughtObject = nullptr;
		finishEvent();
	}
}

void Editor::undo()
{
	if (undoPos >= 1)
	{
		undoPos--;
		auto lastEvent = undoEvents[undoPos];
		for (auto const& subEvent : lastEvent->subEvents)
		{
			switch (lastEvent->type)
			{
			case Create:
				for (auto const& i : ObjMgr.atPosition(subEvent.x, subEvent.y, subEvent.objectIndex))
				{
					Destroy(i);
				}
				break;
			case Remove:
				CreateByIndex(subEvent.objectIndex, subEvent.x, subEvent.y);
				break;
			case Move:
				for (auto const& i : ObjMgr.atPosition(subEvent.newX, subEvent.newY, subEvent.objectIndex))
				{
					i->x = subEvent.oldX;
					i->y = subEvent.oldY;
				}
				break;
			}
		}
	}
}

void Editor::redo()
{
	if (undoPos < undoEvents.size())
	{
		auto lastEvent = undoEvents[undoPos];
		for (auto const& subEvent : lastEvent->subEvents)
		{
			switch (lastEvent->type)
			{
			case Create:
				CreateByIndex(subEvent.objectIndex, subEvent.x, subEvent.y);
				break;
			case Remove:
				for (auto const& i : ObjMgr.atPosition(subEvent.x, subEvent.y, subEvent.objectIndex))
				{
					Destroy(i);
				}
				break;
			case Move:
				for (auto const& i : ObjMgr.atPosition(subEvent.oldX, subEvent.oldY, subEvent.objectIndex))
				{
					i->x = subEvent.newX;
					i->y = subEvent.newY;
				}
				break;
			}
		}
		undoPos++;
	}
}

void Editor::clearUndo()
{
	undoPos = 0;
	undoEvents.clear();
}


