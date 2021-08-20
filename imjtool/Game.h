#pragma once

#include "Editor.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "Gui.h"
#include "InputManager.h"
#include "PlayerManager.h"

// game manager shortcuts
#define Gm Game::get() 
#define ResMgr Game::get().resourceManager
#define ObjMgr Game::get().objectManager
#define InputMgr Game::get().inputManager
#define PlayerMgr Game::get().playerManager

class Game
{
public:
	static Game& get()
	{
		static Game instance;
		return instance;
	}

	ResourceManager resourceManager = ResourceManager();
	ObjectManager objectManager = ObjectManager();
	InputManager inputManager = InputManager();
	PlayerManager playerManager = PlayerManager();
	Gui gui = Gui();
	Editor editor = Editor();

	unique_ptr<sf::RenderWindow> window;
	unique_ptr<sf::RenderTexture> gameTexture;

	sf::Clock deltaClock;
	float fps = 0;

	void run();
	void handleEvent();
	void update();
	void loadTextures();
};
