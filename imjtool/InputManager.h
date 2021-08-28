#pragma once

#define MAX_KEY 256

namespace sf
{
	class Event;
}

class InputManager
{
public:
	bool keyPress[MAX_KEY];
	bool keyRelease[MAX_KEY];

	bool tasPress[MAX_KEY];
	bool tasHold[MAX_KEY];
	bool tasRelease[MAX_KEY];

	bool mouseWheelUp = false;
	bool mouseWheelDown = false;

	void update(sf::Event& event);
	void clearPressAndRelease();

	bool isKeyPress(int key);
	bool isKeyHold(int key);
	bool isKeyRelease(int key);

	bool isKeyPressG(int key);
	bool isKeyHoldG(int key);
	bool isKeyReleaseG(int key);
};

