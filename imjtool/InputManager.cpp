#include "InputManager.h"
#include "Game.h"

void InputManager::update(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) 
	{
		keyPress[event.key.code] = true;
	}
	if (event.type == sf::Event::KeyReleased) 
	{
		keyRelease[event.key.code] = true;
	}
	if (event.type == sf::Event::MouseWheelScrolled)
	{
		// -down +up
		auto dt = event.mouseWheelScroll.delta;
		if (dt < 0)
		{
			mouseWheelDown = true;
		}
		else if (dt > 0)
		{
			mouseWheelUp = true;
		}
	}
}

void InputManager::clearPressAndRelease()
{
	for (auto i = 0; i < MAX_KEY; i++)
	{
		keyPress[i] = false;
		keyRelease[i] = false;
	}
	mouseWheelUp = false;
	mouseWheelDown = false;
}

// normal check (GUI)
bool InputManager::isKeyPress(int key)
{
	return keyPress[key];
}

bool InputManager::isKeyHold(int key)
{
	return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
}

bool InputManager::isKeyRelease(int key)
{
	return keyRelease[key];
}

// in-game check (support TAS)
bool InputManager::isKeyPressG(int key)
{
	return RecMgr.tasPause ? tasPress[key] : keyPress[key];
}

bool InputManager::isKeyHoldG(int key)
{
	return RecMgr.tasPause ? tasHold[key] : sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
}

bool InputManager::isKeyReleaseG(int key)
{
	return RecMgr.tasPause ? tasRelease[key] : keyRelease[key];
}

