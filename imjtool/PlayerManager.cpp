#include "PlayerManager.h"
#include "InGame.h"

void PlayerManager::update()
{
	if (IS_PRESS(sf::Keyboard::R))
	{
		DESTROYN(Player);
		CREATE(Player, currentSave.x, currentSave.y);
	}
}

void PlayerManager::save()
{
	if (player != nullptr) 
	{
		currentSave.x = player->x;
		currentSave.y = player->y;
		currentSave.grav = grav;
		currentSave.face = face;
	}
}

void PlayerManager::load()
{
	if (player != nullptr)
	{
		player->x = currentSave.x;
		player->y = currentSave.y;
		grav = currentSave.grav;
		face = currentSave.face;
	}
}


