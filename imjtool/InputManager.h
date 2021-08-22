#pragma once

#define MAX_KEY 256

namespace sf
{
	class Event;
}

class InputManager
{
	bool keyPress[MAX_KEY];
	bool keyHold[MAX_KEY];
	bool keyRelease[MAX_KEY];

public:
	void update(sf::Event& event);
	void clearPressAndRelease();
	bool isKeyPress(int key);
	bool isKeyHold(int key);
	bool isKeyRelease(int key);
};

