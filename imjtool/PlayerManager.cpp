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
	if (!player.expired()) 
	{
		currentSave.x = player.lock()->x;
		currentSave.y = player.lock()->y;
		currentSave.grav = grav;
		currentSave.face = face;
	}
}

void PlayerManager::load()
{
	DestroyByName(Player);
	DestroyByName(Blood);

	Create(GetIndex(Player), currentSave.x, currentSave.y);

	player.lock()->x = currentSave.x;
	player.lock()->y = currentSave.y;
	grav = currentSave.grav;
	face = currentSave.face;
}


