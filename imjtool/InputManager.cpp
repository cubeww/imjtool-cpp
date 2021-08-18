#include "InputManager.h"
#include "Game.h"

void InputManager::update()
{
	for (auto i = 0; i < MAX_KEY; i++)
	{
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
		{
			if (!keyHold[i])
			{
				keyPress[i] = true;
				keyRelease[i] = false;
			}
			else
			{
				keyPress[i] = false;
				keyRelease[i] = false;
			}
			keyHold[i] = true;
		}
		else
		{
			if (keyHold[i])
			{
				keyPress[i] = false;
				keyRelease[i] = true;
			}
			else
			{
				keyPress[i] = false;
				keyRelease[i] = false;
			}
			keyHold[i] = false;
		}
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

