#include "InputManager.h"
#include "Game.h"

void InputManager::update(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) 
	{
		keyPress[event.key.code] = true;
		keyHold[event.key.code] = true;
	}
	if (event.type == sf::Event::KeyReleased) 
	{
		keyHold[event.key.code] = false;
		keyRelease[event.key.code] = true;
	}
}

void InputManager::clearPressAndRelease()
{
	for (auto i = 0; i < MAX_KEY; i++)
	{
		keyPress[i] = false;
		keyRelease[i] = false;
	}
}

bool InputManager::isKeyPress(int key)
{
	return keyPress[key];
}

bool InputManager::isKeyHold(int key)
{
	return keyHold[key];
}

bool InputManager::isKeyRelease(int key)
{
	return keyRelease[key];
}

