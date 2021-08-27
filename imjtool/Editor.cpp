#include "Editor.h"

#include "Game.h"
#include "Object.h"
#include "InGame.h"

inline float pointdir(float x1, float y1, float x2, float y2)
{
	return atan2(y2 - y1, x2 - x1);
}

inline float pointdist(float x1, float y1, float x2, float y2)
{
	return sqrt(powf(x1 - x2, 2) + powf(y1 - y2, 2));
}

Editor::Editor()
{
}

void Editor::update()
{
	auto mousePos = ImGui::GetMousePos();
	auto windowPos = ImGui::GetWindowPos();
	auto windowSize = ImGui::GetWindowSize();
	auto cursorStartPos = ImGui::GetCursorStartPos();
	auto mouseInPos = ImVec2(mousePos.x - windowPos.x - cursorStartPos.x, mousePos.y - windowPos.y - cursorStartPos.y);

	mouseInTitle = sf::FloatRect(windowPos.x, windowPos.y, windowSize.x, cursorStartPos.y).contains(mousePos.x, mousePos.y);
	auto cursorInArea = sf::FloatRect(0, 0, 799, 607).contains(mouseInPos.x, mouseInPos.y);

	auto leftPress = ImGui::IsMouseClicked(ImGuiMouseButton_Left);
	auto leftHold = ImGui::IsMouseDown(ImGuiMouseButton_Left);
	auto leftRelease = ImGui::IsMouseReleased(ImGuiMouseButton_Left);

	auto rightPress = ImGui::IsMouseClicked(ImGuiMouseButton_Right);
	auto rightHold = ImGui::IsMouseDown(ImGuiMouseButton_Right);
	auto rightRelease = ImGui::IsMouseReleased(ImGuiMouseButton_Right);

	auto dragHold = InputMgr.isKeyHold(sf::Keyboard::Space);
	auto pickerHold = InputMgr.isKeyHold(sf::Keyboard::LControl);
	auto codeHold = InputMgr.isKeyHold(sf::Keyboard::LAlt);

	auto snappedPos = ImVec2(floor(mouseInPos.x / snap.x) * snap.x, floor(mouseInPos.y / snap.y) * snap.y);
	auto focused = ImGui::IsWindowFocused();
	ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);

	if (cursorInArea)
	{
		if (dragHold && focused)
		{
			ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
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
			ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
			if (leftPress)
			{
				auto col = ObjMgr.collisionPointList(mouseInPos.x, mouseInPos.y, ALL);
				for (auto const& i : col)
				{
					selectIndex = i->index;
				}
			}
		}
		else if (codeHold && focused)
		{
			ImGui::SetMouseCursor(ImGuiMouseCursor_TextInput);
		}
		else
		{
			if (leftHold && !ImGui::IsPopupOpen(nullptr, ImGuiPopupFlags_AnyPopupId))
			{
				if (leftPress) 
				{
					finishCreateObject(snappedPos.x, snappedPos.y);
				}
				else if (leftHoldLast)
				{
					auto dir = pointdir(mouseLastPos.x, mouseLastPos.y, mouseInPos.x, mouseInPos.y);
					auto n = floor(pointdist(mouseLastPos.x, mouseLastPos.y, mouseInPos.x, mouseInPos.y));
					auto len = 1;
					auto dx = len * cos(dir);
					auto dy = len * sin(dir);
					auto xx = mouseLastPos.x;
					auto yy = mouseLastPos.y;
					auto xxnLast = NAN;
					auto yynLast = NAN;
					for (auto i = 0; i < n; i++)
					{
						auto xxn = floor(xx / snap.x) * snap.x;
						auto yyn = floor(yy / snap.y) * snap.y;
						if (!equalF(xxn, xxnLast) || !equalF(yyn, yynLast)) {
							xxnLast = xxn;
							yynLast = yyn;
							finishCreateObject(xxn, yyn);
						}
						xx += dx;
						yy += dy;
					}
				}
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
					if (i->index == GetIndex(PlayerStart) || !inPalette(i->index))
					{
						continue;
					}
					addRemoveEvent(i->x, i->y, i->index);
					DestroyInst(i);
				}
			}
		}
		if (!dragHold)
		{
			finishMoveObject();
		}

		// press W to spawn kid
		if (InputMgr.isKeyPress(sf::Keyboard::W))
		{
			DestroyByName(Player);
			DestroyByName(Blood);
			CreateInst(GetIndex(Player), mouseInPos.x, mouseInPos.y);
		}
	}

	if (leftRelease || rightRelease)
	{
		finishEvent();
	}

	mouseLastPos.x = mouseInPos.x;
	mouseLastPos.y = mouseInPos.y;
	leftHoldLast = leftHold;
	rightHoldLast = rightHold;

	if (cursorInArea && !dragHold && !pickerHold && !codeHold)
	{
		// draw preview
		auto spr = SkinMgr.getCurrentSprite(spriteOf(selectIndex));
		ImGui::SetCursorPos(ImVec2(snappedPos.x + cursorStartPos.x - spr->xOrigin, snappedPos.y + cursorStartPos.y - spr->yOrigin));
		ImGui::Image(*spr->items[0]->sprite, sf::Color(255, 255, 255, 100));
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
		auto inst = CreateInst(selectIndex, x, y);
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
					DestroyInst(i);
				}
				break;
			case Remove:
				CreateInst(subEvent.objectIndex, subEvent.x, subEvent.y);
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
				CreateInst(subEvent.objectIndex, subEvent.x, subEvent.y);
				break;
			case Remove:
				for (auto const& i : ObjMgr.atPosition(subEvent.x, subEvent.y, subEvent.objectIndex))
				{
					DestroyInst(i);
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


