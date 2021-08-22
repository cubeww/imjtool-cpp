#pragma once
#include <string>
#include <vector>

#include "imgui.h"
#include "imgui-SFML.h"
#include "ObjectManager.h"

class Sprite;
class Object;

using namespace std;
using namespace ImGui;

struct SubEvent
{
	float x = 0, y = 0, oldX = 0, oldY = 0, newX = 0, newY = 0;
	int objectIndex = -1;

	SubEvent(float _x, float _y, int _objectIndex)
	{
		x = _x;
		y = _y;
		objectIndex = _objectIndex;
	}

	SubEvent(int _objectIndex, float _oldX, float _oldY, float _newX, float _newY)
	{
		objectIndex = _objectIndex;
		oldX = _oldX;
		oldY = _oldY;
		newX = _newX;
		newY = _newY;
	}
};

enum UndoEventType
{
	Create,
	Remove,
	Move,
};

struct UndoEvent
{
	int type;
	vector<SubEvent> subEvents;

	UndoEvent(int _type)
	{
		type = _type;
	}

	void addSubEvent(SubEvent subevent)
	{
		subEvents.push_back(subevent);
	}
};

class Editor
{
public:
	Editor();
	shared_ptr<Sprite> selectSprite;
	int selectIndex = 0;
	ImVec2 snap = ImVec2(32, 32);

	shared_ptr<Object> caughtObject;
	ImVec2 caughtOldPos;
	ImVec2 mouseLastPos;

	vector<shared_ptr<UndoEvent>> undoEvents;
	shared_ptr<UndoEvent> curEvent;
	size_t undoPos = 0;
	bool leftHoldLast = false;
	bool rightHoldLast = false;
	bool mouseInTitle = false;

	void update();

	void addCreateEvent(float x, float y, int objectIndex);
	void addRemoveEvent(float x, float y, int objectIndex);
	void addMoveEvent(shared_ptr<Object> object, float oldX, float oldY, float newX, float newY);
	void finishEvent();
	void finishCreateObject(float x, float y);
	void finishMoveObject();

	void undo();
	void redo();
	void clearUndo();
};
