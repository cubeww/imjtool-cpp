#include "RecordManager.h"
#include "Game.h"

void RecordManager::nextFrame()
{
	if (tasPause)
	{
		ObjMgr.update();

		if (autoClearPress)
		{
			for (auto i = 0; i < MAX_KEY; i++)
			{
				InputMgr.tasPress[i] = false;
			}
		}
		if (autoClearHold)
		{
			for (auto i = 0; i < MAX_KEY; i++)
			{
				InputMgr.tasHold[i] = false;
			}
		}
		if (autoClearRelease)
		{
			for (auto i = 0; i < MAX_KEY; i++)
			{
				InputMgr.tasRelease[i] = false;
			}
		}
	}
}

void RecordManager::saveState()
{
	auto state = PlayerMgr.saveState();
	if (state != nullptr)
	{
		states.push_back(state);
	}
}

void RecordManager::loadState(int index)
{
	PlayerMgr.loadState(states[index]);
}

void RecordManager::deleteState(int index)
{
	states.erase(states.begin() + index);
}
