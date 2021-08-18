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
				auto addObject = [&](string spriteName)
				{
					if (ImageButton(*Game::get().resourceManager.textures[spriteName]))
					{
						Game::get().editor.selectSprite = Game::get().resourceManager.sprites[spriteName];
					}
				};

				addObject("spike_up");
				SameLine();
				addObject("spike_down");
				SameLine();
				addObject("spike_left");
				SameLine();
				addObject("spike_right");

				addObject("mini_spike_up");
				SameLine();
				addObject("mini_spike_down");
				SameLine();
				addObject("mini_spike_left");
				SameLine();
				addObject("mini_spike_right");
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
