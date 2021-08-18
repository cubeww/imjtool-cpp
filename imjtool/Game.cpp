#include "Game.h"

#include <imgui-SFML.h>

#include "InGame.h"

void Game::run()
{
	gameTexture = make_unique<sf::RenderTexture>();
	gameTexture->create(800, 608);

	window = make_unique<sf::RenderWindow>(sf::VideoMode(1280, 720), "ImJtool");
	window->setFramerateLimit(50);

	SFML::Init(*window);

	createResources();
	createObjects();

	editor.selectSprite = resourceManager.sprites["block"];
	editor.selectIndex = GETID(Block);

	while (window->isOpen())
	{
		handleEvent();
		update();
	}
}

void Game::handleEvent()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		SFML::ProcessEvent(event);

		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void Game::update()
{
	SFML::Update(*window, deltaClock.restart());
	window->clear();
	gameTexture->clear(sf::Color::White);
	inputManager.update();
	objectManager.update();
	gui.update();
	SFML::Render(*window);
	window->display();
	fps = 1.f / deltaClock.getElapsedTime().asSeconds();
}

void Game::createResources()
{
	resourceManager.createTexture("apple", "textures/apple.png");
	resourceManager.createTexture("block", "textures/block.png");
	resourceManager.createTexture("blood", "textures/blood.png");
	resourceManager.createTexture("bullet", "textures/bullet.png");
	resourceManager.createTexture("gravity_down", "textures/gravity_down.png");
	resourceManager.createTexture("gravity_up", "textures/gravity_up.png");
	resourceManager.createTexture("jump_refresher", "textures/jump_refresher.png");
	resourceManager.createTexture("killer_block", "textures/killer_block.png");
	resourceManager.createTexture("mini_spike_down", "textures/mini_spike_down.png");
	resourceManager.createTexture("mini_spike_left", "textures/mini_spike_left.png");
	resourceManager.createTexture("mini_spike_right", "textures/mini_spike_right.png");
	resourceManager.createTexture("mini_spike_up", "textures/mini_spike_up.png");
	resourceManager.createTexture("platform", "textures/platform.png");
	resourceManager.createTexture("player_fall", "textures/player_fall.png");
	resourceManager.createTexture("player_idle", "textures/player_idle.png");
	resourceManager.createTexture("player_jump", "textures/player_jump.png");
	resourceManager.createTexture("player_running", "textures/player_running.png");
	resourceManager.createTexture("player_sliding", "textures/player_sliding.png");
	resourceManager.createTexture("save", "textures/save.png");
	resourceManager.createTexture("spike_down", "textures/spike_down.png");
	resourceManager.createTexture("spike_left", "textures/spike_left.png");
	resourceManager.createTexture("spike_right", "textures/spike_right.png");
	resourceManager.createTexture("spike_up", "textures/spike_up.png");
	resourceManager.createTexture("walljump_l", "textures/walljump_l.png");
	resourceManager.createTexture("walljump_r", "textures/walljump_r.png");
	resourceManager.createTexture("warp", "textures/warp.png");
	resourceManager.createTexture("water", "textures/water.png");
	resourceManager.createTexture("player_mask", "textures/player_mask.png");
	resourceManager.createTexture("player_mask_flip", "textures/player_mask_flip.png");
	resourceManager.createTexture("player_start", "textures/player_start.png");
	resourceManager.createTexture("mini_block", "textures/mini_block.png");

	resourceManager.createSprite("apple").addSheet("apple", 2);
	resourceManager.createSprite("block").addSheet("block");
	resourceManager.createSprite("blood").addSheet("blood", 3);
	resourceManager.createSprite("bullet").addSheet("bullet", 2);
	resourceManager.createSprite("gravity_down").addSheet("gravity_down");
	resourceManager.createSprite("gravity_up").addSheet("gravity_up");
	resourceManager.createSprite("jump_refresher").addSheet("jump_refresher");
	resourceManager.createSprite("killer_block").addSheet("killer_block");
	resourceManager.createSprite("mini_spike_down").addSheet("mini_spike_down");
	resourceManager.createSprite("mini_spike_left").addSheet("mini_spike_left");
	resourceManager.createSprite("mini_spike_right").addSheet("mini_spike_right");
	resourceManager.createSprite("mini_spike_up").addSheet("mini_spike_up");
	resourceManager.createSprite("platform").addSheet("platform");
	resourceManager.createSprite("player_fall").addSheet("player_fall", 2);
	resourceManager.createSprite("player_idle").addSheet("player_idle", 4);
	resourceManager.createSprite("player_jump").addSheet("player_jump", 2);
	resourceManager.createSprite("player_running").addSheet("player_running", 4);
	resourceManager.createSprite("player_sliding").addSheet("player_sliding", 2);
	resourceManager.createSprite("save").addSheet("save", 2);
	resourceManager.createSprite("spike_down").addSheet("spike_down");
	resourceManager.createSprite("spike_left").addSheet("spike_left");
	resourceManager.createSprite("spike_right").addSheet("spike_right");
	resourceManager.createSprite("spike_up").addSheet("spike_up");
	resourceManager.createSprite("walljump_l").addSheet("walljump_l");
	resourceManager.createSprite("walljump_r").addSheet("walljump_r");
	resourceManager.createSprite("warp").addSheet("warp");
	resourceManager.createSprite("water").addSheet("water");
	resourceManager.createSprite("player_mask").addSheet("player_mask");
	resourceManager.createSprite("player_mask_flip").addSheet("player_mask_flip");
	resourceManager.createSprite("player_start").addSheet("player_start");
	resourceManager.createSprite("mini_block").addSheet("mini_block");
}

void Game::createObjects()
{
}
