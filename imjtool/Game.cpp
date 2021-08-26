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

	ImGui::SFML::Init(*window);

	resourceManager.loadTextures();
	resourceManager.loadSounds();
	skinManager.loadConfig();
	configManager.load();

	editor.selectIndex = GetIndex(Block);

	CreateInst(GetIndex(Bg), 0, 0);
	CreateInst(GetIndex(Grid), 0, 0);

	while (window->isOpen())
	{
		handleEvent();
		update();
	}
	ImGui::SFML::Shutdown();
}

void Game::handleEvent()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);

		if (event.type == sf::Event::Closed) 
		{
			configManager.save();
			window->close();
		}

		InputMgr.update(event);
	}
}

void Game::update()
{
	ImGui::SFML::Update(*window, deltaClock.restart());
	window->clear(windowBgColor);
	gameTexture->clear(sf::Color::White);
	playerManager.update();
	objectManager.update();
	gui.update();
	inputManager.clearPressAndRelease();
	ImGui::SFML::Render(*window);
	window->display();
	fps = round(1.f / deltaClock.getElapsedTime().asSeconds());
}
