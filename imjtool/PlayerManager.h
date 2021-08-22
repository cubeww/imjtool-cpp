#pragma once

#include <iostream>

using namespace std;

class Player;

struct PlayerSave
{
	float x = -1;
	float y = -1;
	float face = 1;
	float grav = 1;
};

enum class ShowMask
{
	OnlyPlayer,
	OnlyMask,
	PlayerAndMask,
};

enum class SaveType
{
	OnlyShoot,
	ShootOrBullet,
};

enum class DeathBorder
{
	Killer,
	Solid,
};

class PlayerManager
{
public:
	PlayerSave currentSave;
	shared_ptr<Player> player;

	float face = 1;
	float grav = 1;
	bool dotkid = false;
	bool dotkidOutline = false;
	bool deathEnable = true;
	bool infjump = false;
	ShowMask showMask = ShowMask::OnlyMask;
	SaveType saveType = SaveType::OnlyShoot;
	DeathBorder deathBorder = DeathBorder::Killer;

	void update();
	void save();
	void load();
};

