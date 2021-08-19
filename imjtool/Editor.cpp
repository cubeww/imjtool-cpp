#include "Editor.h"

#include "Game.h"
#include "Object.h"

#define pointdir(x1, y1, x2, y2) (atan((y1 - y2) / (x1 - x2)))
#define pointdist(x1, y1, x2, y2) (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)))

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

	auto dragHold = IS_HOLD(sf::Keyboard::Space);
	auto pickerHold = IS_HOLD(sf::Keyboard::LControl);
	auto codeHold = IS_HOLD(sf::Keyboard::LAlt);

	auto& mgr = Game::get().objectManager;
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
					for (auto i : mgr.objects)
					{
						auto col = mgr.collisionPoint(mouseInPos.x, mouseInPos.y, i->index);
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
				auto col = mgr.collisionPointList(mouseInPos.x, mouseInPos.y, ALL);
				for (auto i : col)
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
					col = mgr.collisionLineList(mouseLastPos.x, mouseLastPos.y, mouseInPos.x, mouseInPos.y, ALL);
				}
				else
				{
					col = mgr.collisionPointList(mouseInPos.x, mouseInPos.y, ALL);
				}
				for (auto i : col)
				{
					if (i->index == GETID(PlayerStart) || i->index == GETID(Player))
					{
						continue;
					}
					addRemoveEvent(i->x, i->y, i->index);
					DESTROY(i);
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
	if (IS_HOLD(sf::Keyboard::LControl) && IS_PRESS(sf::Keyboard::Z))
	{
		undo();
	}
	if (IS_HOLD(sf::Keyboard::LControl) && IS_PRESS(sf::Keyboard::Y))
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
	if (Game::get().objectManager.atPosition(x, y, selectIndex).empty())
	{
		auto inst = CREATEI(selectIndex, x, y);
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
	auto& mgr = Game::get().objectManager;
	if (undoPos >= 1)
	{
		undoPos--;
		auto lastEvent = undoEvents[undoPos];
		for (auto subEvent : lastEvent->subEvents)
		{
			switch (lastEvent->type)
			{
			case Create:
				for (auto i : mgr.atPosition(subEvent.x, subEvent.y, subEvent.objectIndex))
				{
					DESTROY(i);
				}
				break;
			case Remove:
				CREATEI(subEvent.objectIndex, subEvent.x, subEvent.y);
				break;
			case Move:
				for (auto i : mgr.atPosition(subEvent.newX, subEvent.newY, subEvent.objectIndex))
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
	auto& mgr = Game::get().objectManager;
	if (undoPos < undoEvents.size())
	{
		auto lastEvent = undoEvents[undoPos];
		for (auto subEvent : lastEvent->subEvents)
		{
			switch (lastEvent->type)
			{
			case Create:
				CREATEI(subEvent.objectIndex, subEvent.x, subEvent.y);
				break;
			case Remove:
				for (auto i : mgr.atPosition(subEvent.x, subEvent.y, subEvent.objectIndex))
				{
					DESTROY(i);
				}
				break;
			case Move:
				for (auto i : mgr.atPosition(subEvent.oldX, subEvent.oldY, subEvent.objectIndex))
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
	
}


