#include "gui.h"

#include "Game.h"
#include <imgui-SFML.h>

void Gui::mainMenu()
{
	if (BeginMainMenuBar())
	{
		if (BeginMenu("File"))
		{
			if (MenuItem("New"))
			{
				showGameWindow = true;
			}
			Separator();
			if (MenuItem("Exit"))
			{
				Game::get().window->close();
			}
			EndMenu();
		}
		if (BeginMenu("Map"))
		{
			EndMenu();
		}
		if (BeginMenu("Player"))
		{
			EndMenu();
		}
		if (BeginMenu("Window"))
		{
			EndMenu();
		}
		if (BeginMenu("Help"))
		{
			EndMenu();
		}
		EndMainMenuBar();
	}
}

void Gui::gameWindow()
{
	if (showGameWindow)
	{
		SetNextWindowSize(ImVec2(816, 650), ImGuiCond_Once);
		if (Begin("Game Window", &showGameWindow, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
		{
			Image(*Game::get().gameTexture);
			Game::get().editor.update();
			End();
		}
	}
	if (showPalette)
	{
		SetNextWindowSize(ImVec2(200, 300), ImGuiCond_Once);
		if (Begin("Palette", &showPalette))
		{
			if (CollapsingHeader("Killers"))
			{
				auto addObject = [&](int index, string spriteName)
				{
					if (paletteIcons[index] == nullptr)
					{
						auto spr = Game::get().resourceManager.sprites[spriteName]->items[0]->sprite;
						spr->setPosition(16, 16);
						spr->setOrigin(spr->getLocalBounds().width / 2, spr->getLocalBounds().height / 2);
						auto tex = make_shared<sf::RenderTexture>();
						tex->create(32, 32);
						tex->clear(sf::Color::Transparent);
						tex->draw(*spr);
						paletteIcons[index] = tex;
					}

					if (ImageButton(*paletteIcons[index]))
					{
						Game::get().editor.selectIndex = index;
						Game::get().editor.selectSprite = Game::get().resourceManager.sprites[spriteName];
					}
				};

				addObject(GETID(SpikeUp),"spike_up");
				SameLine();
				addObject(GETID(SpikeDown), "spike_down");
				SameLine();
				addObject(GETID(SpikeLeft), "spike_left");
				SameLine();
				addObject(GETID(SpikeRight), "spike_right");

				addObject(GETID(SpikeUp), "player_idle");
				SameLine();
				addObject(GETID(SpikeUp), "mini_spike_down");
				SameLine();
				addObject(GETID(SpikeUp), "mini_spike_left");
				SameLine();
				addObject(GETID(SpikeUp), "mini_spike_right");
			}
			End();
		}
	}
}

void Gui::update()
{
	mainMenu();
	gameWindow();
}
