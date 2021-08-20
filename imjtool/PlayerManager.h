#pragma once

#include <iostream>

using namespace std;

class Player;

#define CUR_SAVE Game::get().playerManager.currentSave
#define CUR_FACE Game::get().playerManager.face
#define CUR_GRAV Game::get().playerManager.grav

struct PlayerSave
{
	float x = -1;
	float y = -1;
	float face = 1;
	float grav = 1;
};

class PlayerManager
{
public:
	PlayerSave currentSave;
	shared_ptr<Player> player;

	float face = 1;
	float grav = 1;

	void update();
	void save();
	void load();
};

