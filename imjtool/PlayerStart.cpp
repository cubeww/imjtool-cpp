#include "PlayerStart.h"

PlayerStart::PlayerStart()
{
	setSprite("player_start");
}

void PlayerStart::update()
{
	drawSelf();
}
