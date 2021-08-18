#pragma once
#include "Object.h"

class Player : public Object
{
public:
	float jump = 8.5;
	float jump2 = 7;
	float maxHspeed = 3;
	float maxVspeed = 9;
	bool onPlatform = false;
	int grav = 1;
	int face = 1;
	bool djump = true;

	Player();
	void update() override;
};

