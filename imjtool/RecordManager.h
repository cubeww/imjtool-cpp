#pragma once
#include <vector>
#include <memory>

struct PlayerState;

using namespace std;
class RecordManager
{
public:
	bool tasPause = false;
	bool autoClearPress = true;
	bool autoClearHold = false;
	bool autoClearRelease = true;

	void nextFrame();
	void saveState();
	void loadState(int index);
	void deleteState(int index);

	vector<shared_ptr<PlayerState>> states;
};

