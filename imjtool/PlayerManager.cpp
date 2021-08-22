#include "PlayerManager.h"
#include "InGame.h"

void PlayerManager::update()
{
	if (InputMgr.isKeyPress(sf::Keyboard::R))
	{
		load();
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
	DestroyByName(Player);
	DestroyByName(Blood);

	Create(GetIndex(Player), currentSave.x, currentSave.y);

	player->x = currentSave.x;
	player->y = currentSave.y;
	grav = currentSave.grav;
	face = currentSave.face;
}


