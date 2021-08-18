#pragma once

#define MAX_KEY 256

class InputManager
{
private:
	bool keyPress[MAX_KEY];
	bool keyHold[MAX_KEY];
	bool keyRelease[MAX_KEY];
public:
	void update();
	bool isKeyPress(int key);
	bool isKeyHold(int key);
	bool isKeyRelease(int key);
};

