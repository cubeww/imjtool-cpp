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
	skinManager.apply("<default>");
	configManager.load();

	sf::Image icon = resourceManager.textures["icon"]->copyToImage();
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	editor.selectIndex = GetIndex(Block);
	gui.curGroup = 4;

	CreateInst(GetIndex(Bg), 0, 0);
	CreateInst(GetIndex(Grid), 0, 0);
	CreateInst(GetIndex(BorderBlock), 0, -32)->xscale = 25;
	CreateInst(GetIndex(BorderBlock), 0, 608)->xscale = 25;
	CreateInst(GetIndex(BorderBlock), -32, 0)->yscale = 19;
	CreateInst(GetIndex(BorderBlock), 800, 0)->yscale = 19;

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
	playerManager.update();
	if (!recordManager.tasPause)
	{
		objectManager.update();
	}
	gui.update();
	inputManager.clearPressAndRelease();
	ImGui::SFML::Render(*window);
	window->display();
	fps = round(1.f / deltaClock.getElapsedTime().asSeconds());
}
