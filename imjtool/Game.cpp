#include "Game.h"

#include <imgui-SFML.h>
#include <fstream>
#include <filesystem>

#include "InGame.h"
#include "json.hpp"

using namespace nlohmann;

void Game::run()
{
	gameTexture = make_unique<sf::RenderTexture>();
	gameTexture->create(800, 608);

	window = make_unique<sf::RenderWindow>(sf::VideoMode(1280, 720), "ImJtool");
	window->setFramerateLimit(50);
	window->setKeyRepeatEnabled(false);

	SFML::Init(*window);

	loadTextures();
	skinManager.loadConfig();

	editor.selectSprite = resourceManager.sprites["block"];
	editor.selectIndex = GetIndex(Block);

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

		InputMgr.update(event);
	}
}

void Game::update()
{
	SFML::Update(*window, deltaClock.restart());
	window->clear();
	gameTexture->clear(sf::Color::White);
	playerManager.update();
	objectManager.update();
	gui.update();
	inputManager.clearPressAndRelease();
	SFML::Render(*window);
	window->display();
	fps = round(1.f / deltaClock.getElapsedTime().asSeconds());
}

void Game::loadTextures()
{
	ifstream f("textures/define.json");
	json j;
	f >> j;
	for (auto i : j)
	{
		string filename = i["file"];
		string name = filesystem::path(filename).stem().string();

		auto x = 1;
		auto y = 1;
		if (i["x"] != nullptr)
			x = i["x"];
		if (i["y"] != nullptr)
			y = i["y"];

		resourceManager.createTexture(name, "textures/" + filename);
		resourceManager.createSprite(name).addSheet(name, x, y);
	}
	f.close();

	f.open("sfx/define.json");
	f >> j;
	for (auto i : j)
	{
		string filename = i["file"];
		string name = filesystem::path(filename).stem().string();

		auto x = 1;
		auto y = 1;
		if (i["x"] != nullptr)
			x = i["x"];
		if (i["y"] != nullptr)
			y = i["y"];

		resourceManager.createSound(name, "sfx/" + filename);
	}
	f.close();
}
