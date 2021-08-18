#include "Editor.h"

#include "Game.h"
#include "Object.h"

#define pointdir(x1, y1, x2, y2) (atan((y1 - y2) / (x2 - x1)))
#define pointdist(x1, y1, x2, y2) (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)))

Editor::Editor()
{
}

void Editor::update()
{
	auto mousePos = GetMousePos();
	auto windowPos = GetWindowPos();
	auto cursorStartPos = GetCursorStartPos();
	auto mouseInPos = ImVec2(mousePos.x - windowPos.x - cursorStartPos.x, mousePos.y - windowPos.y - cursorStartPos.y);

	auto cursorInArea = sf::FloatRect(0, 0, 799, 607).contains(mouseInPos.x, mouseInPos.y);

	auto leftPress = IsMouseClicked(ImGuiMouseButton_Left);
	auto leftHold = IsMouseDown(ImGuiMouseButton_Left);
	auto leftRelease = IsMouseDown(ImGuiMouseButton_Left);

	auto rightPress = IsMouseClicked(ImGuiMouseButton_Right);
	auto rightHold = IsMouseDown(ImGuiMouseButton_Right);
	auto rightRelease = IsMouseDown(ImGuiMouseButton_Right);

	auto dragHold = IS_HOLD(sf::Keyboard::Space);
	auto pickerHold = IS_HOLD(sf::Keyboard::LControl);
	auto codeHold = IS_HOLD(sf::Keyboard::LAlt);

	auto& mgr = Game::get().objectManager;

	if (cursorInArea)
	{
		auto snappedPos = ImVec2(floor(mouseInPos.x / snap.x) * snap.x, floor(mouseInPos.y / snap.y) * snap.y);

		SetCursorPos(ImVec2(snappedPos.x + cursorStartPos.x, snappedPos.y + cursorStartPos.y));
		Image(*selectSprite->items[0]->sprite, sf::Color(255, 255, 255, 100));

		if (dragHold)
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
					caughtOldPos = ImVec2(snappedPos.x, snappedPos.y);
				}
			}
			if (leftRelease)
			{
				finishMoveObject();
			}
		}
		else if (pickerHold)
		{
			if (leftPress)
			{
				auto col = mgr.collisionPointList(mouseInPos.x, mouseInPos.y, -1);
				for (auto i : col)
				{
					selectSprite = i->sprite;
					selectIndex = i->index;
				}
			}
		}
		else if (codeHold)
		{
			// TODO
		}
		else
		{
			if (leftHold)
			{
				// TODO
				/*if (leftHoldLast)
				{
					auto dir = pointdir(mouseLastPos.x, mouseLastPos.y, mouseInPos.x, mouseInPos.y);
					auto n = floor(pointdist(mouseLastPos.x, mouseLastPos.y, mouseInPos.x, mouseInPos.y));

				}*/
				finishCreateObject(snappedPos.x, snappedPos.y);
			}
			else if (rightHold)
			{
				// TODO
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
		curEvent = make_shared<UndoEvent>(Remove);
	}
	curEvent->addSubEvent(SubEvent(object, oldX, oldY, newX, newY));
}

void Editor::finishEvent()
{
	if (curEvent != nullptr)
	{
		// clean useless events
		auto size = undoEvents.size();
		for (auto i = undoPos; i < size; i++)
		{
			undoEvents.erase(undoEvents.begin() + i);
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
