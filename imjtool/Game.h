#pragma once

#include "Editor.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "Gui.h"
#include "InputManager.h"

#define IS_PRESS(key) Game::get().inputManager.isKeyPress(key)
#define IS_HOLD(key) Game::get().inputManager.isKeyHold(key)
#define IS_RELEASE(key) Game::get().inputManager.isKeyRelease(key)

class Game
{
public:
	static Game& get()
	{
		static Game instance;
		return instance;
	}

	ResourceManager resourceManager;
	ObjectManager objectManager;
	InputManager inputManager;
	Gui gui;
	Editor editor;

	unique_ptr<sf::RenderWindow> window;
	unique_ptr<sf::RenderTexture> gameTexture;

	sf::Clock deltaClock;

	void run();
	void handleEvent();
	void update();
	void createResources();
	void createObjects();
};
