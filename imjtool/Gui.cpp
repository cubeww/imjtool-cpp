#include "gui.h"

#include "Game.h"
#include <imgui-SFML.h>

#include "Object.h"

namespace Win
{
#include <windows.h>
}


void Gui::mainMenu()
{
	if (BeginMainMenuBar())
	{
		if (BeginMenu("File"))
		{
			if (MenuItem("New Map", "F2"))
			{
				showGameWindow = true;
			}
			Separator();
			if (MenuItem("Open Map", "CTRL+O"))
			{
				showGameWindow = true;
			}
			if (MenuItem("Save Map", "CTRL+S"))
			{
				showGameWindow = true;
			}
			Separator();
			if (MenuItem("Exit", "ALT+F4"))
			{
				Game::get().window->close();
			}
			EndMenu();
		}
		if (BeginMenu("Edit"))
		{
			if (MenuItem("Undo", "CTRL+Z", false, Game::get().editor.undoPos > 0))
			{
				Game::get().editor.undo();
			}
			if (MenuItem("Redo", "CTRL+Y", false, Game::get().editor.undoPos < Game::get().editor.undoEvents.size()))
			{
				Game::get().editor.redo();
			}
			Separator();
			if (MenuItem("Shift"))
			{
				showShift = true;
			}
			EndMenu();
		}
		if (BeginMenu("View"))
		{
			if (MenuItem("Grid", "F2"))
			{
				showGameWindow = true;
			}
			Separator();
			EndMenu();
		}
		if (BeginMenu("Player"))
		{
			EndMenu();
		}
		if (BeginMenu("Window"))
		{
			if (MenuItem("Game Window", nullptr, showGameWindow))
			{
				showGameWindow = !showGameWindow;
			}
			if (MenuItem("Palette", nullptr, showPalette))
			{
				showPalette = !showPalette;
			}
			if (MenuItem("Debug Window", nullptr, showDebug))
			{
				showDebug = !showDebug;
			}
			EndMenu();
		}
		if (BeginMenu("Help"))
		{
			if (MenuItem("Github"))
			{
				Win::ShellExecuteA(nullptr, "open", "https://github.com/cubeww/imjtool", nullptr, nullptr, 10);
			}
			Separator();
			if (MenuItem("About"))
			{
				showAbout = !showAbout;
			}
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
		int flag = ImGuiWindowFlags_NoResize;
		if (!Game::get().editor.mouseInTitle)
			flag |= ImGuiWindowFlags_NoMove;
		if (Begin("Game Window", &showGameWindow, flag))
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
			if (CollapsingHeader("Player"))
			{
				addObject(GETID(PlayerStart), "player_start");
				SameLine();
				addObject(GETID(Save), "save");
				SameLine();
				addObject(GETID(Warp), "warp");
			}
			if (CollapsingHeader("Killer"))
			{
				addObject(GETID(SpikeUp), "spike_up");
				SameLine();
				addObject(GETID(SpikeDown), "spike_down");
				SameLine();
				addObject(GETID(SpikeLeft), "spike_left");
				SameLine();
				addObject(GETID(SpikeRight), "spike_right");

				addObject(GETID(MiniSpikeUp), "mini_spike_up");
				SameLine();
				addObject(GETID(MiniSpikeDown), "mini_spike_down");
				SameLine();
				addObject(GETID(MiniSpikeLeft), "mini_spike_left");
				SameLine();
				addObject(GETID(MiniSpikeRight), "mini_spike_right");

				addObject(GETID(Apple), "apple");
				SameLine();
				addObject(GETID(KillerBlock), "killer_block");
			}
			if (CollapsingHeader("Block & Platform"))
			{
				addObject(GETID(Block), "block");
				SameLine();
				addObject(GETID(MiniBlock), "mini_block");
				SameLine();
				addObject(GETID(Platform), "platform");
			}
			if (CollapsingHeader("Vine & Water"))
			{
				addObject(GETID(WalljumpR), "walljump_r");
				SameLine();
				addObject(GETID(WalljumpL), "walljump_l");
				SameLine();
				addObject(GETID(Water), "water");
			}
			End();
		}
	}
}

void Gui::debugWindow()
{
	if (showDebug)
	{
		auto debugValue = [&](string name, double value)
		{
			name += ": ";
			string s = to_string(value);
			s.erase(s.find_last_not_of('0') + 1, std::string::npos);
			s.erase(s.find_last_not_of('.') + 1, std::string::npos);
			Text((name + s).data());
		};

		SetNextWindowSize(ImVec2(250, 250), ImGuiCond_Once);
		if (Begin("Debug Window", &showDebug))
		{
			debugValue("FPS", Game::get().fps);
			debugValue("Inst", Game::get().objectManager.objects.size());
			debugValue("Texture Count", Game::get().resourceManager.textures.size());
			debugValue("Sprite Count", Game::get().resourceManager.sprites.size());
			debugValue("Undo Stack Size", Game::get().editor.undoEvents.size());
			debugValue("Undo Pos", Game::get().editor.undoPos);
			if (Button("DEL Instances"))
			{
				DESTROYALL();
			}
			End();
		}
	}
}


void Gui::update()
{
	mainMenu();
	gameWindow();
	debugWindow();
	aboutWindow();
	shiftWindow();
}

void Gui::aboutWindow()
{
	if (showAbout)
	{
		OpenPopup("About");
	}

	SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Once);
	if (BeginPopupModal("About", &showAbout))
	{
		Text("ImJtool");
		Text("By Cube");
		if (Button("Close"))
		{
			showAbout = false;
			CloseCurrentPopup();
		}
		EndPopup();
	}
}

void Gui::shiftWindow()
{
	if (showShift)
	{
		//SetNextWindowSize(ImVec2(250, 250), ImGuiCond_Once);
		if (Begin("Shift Objects", &showShift))
		{
			InputInt("Shift X", &shiftX);
			InputInt("Shift Y", &shiftY);

			SetCursorPos(ImVec2(48, GetCursorPos().y));

			if (Button("U", ImVec2(32, 32)))
			{
				for (auto i : Game::get().objectManager.objects)
				{
					if (i->index == GETID(Player))
						continue;
					Game::get().editor.addMoveEvent(i, i->x, i->y, i->x, i->y - shiftY);
					i->y -= shiftY;
				}
				Game::get().editor.finishEvent();
			}
			if (Button("L", ImVec2(32, 32)))
			{
				for (auto i : Game::get().objectManager.objects)
				{
					if (i->index == GETID(Player))
						continue;
					Game::get().editor.addMoveEvent(i, i->x, i->y, i->x - shiftX, i->y);
					i->x -= shiftX;
				}
				Game::get().editor.finishEvent();
			}
			SameLine();
			if (Button("D", ImVec2(32, 32)))
			{
				for (auto i : Game::get().objectManager.objects)
				{
					if (i->index == GETID(Player))
						continue;
					Game::get().editor.addMoveEvent(i, i->x, i->y, i->x, i->y + shiftY);
					i->y += shiftY;
				}
				Game::get().editor.finishEvent();
			}
			SameLine();
			if (Button("R", ImVec2(32, 32)))
			{
				for (auto i : Game::get().objectManager.objects)
				{
					if (i->index == GETID(Player))
						continue;
					Game::get().editor.addMoveEvent(i, i->x, i->y, i->x + shiftX, i->y);
					i->x += shiftX;
				}
				Game::get().editor.finishEvent();
			}

			End();
		}
	}
}
