#include "gui.h"

#include "Game.h"
#include <imgui-SFML.h>

#include "Object.h"
#include "InGame.h"

#include "imgui_stdlib.h"

//
//namespace Win
//{
//#include <windows.h>
//}

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
				Gm.window->close();
			}
			EndMenu();
		}
		if (BeginMenu("Edit", showGameWindow))
		{
			if (MenuItem("Undo", "CTRL+Z", false, Gm.editor.undoPos > 0))
			{
				Gm.editor.undo();
			}
			if (MenuItem("Redo", "CTRL+Y", false, Gm.editor.undoPos < Gm.editor.undoEvents.size()))
			{
				Gm.editor.redo();
			}
			Separator();
			if (MenuItem("Shift"))
			{
				showShift = true;
			}
			EndMenu();
		}
		if (BeginMenu("View", showGameWindow))
		{
			if (BeginMenu("Grid"))
			{
				if (MenuItem("Show Grid", nullptr, showGrid))
				{
					showGrid = !showGrid;
					if (showGrid)
					{
						updateGrid();
					}
				}
				Separator();
				if (MenuItem("Set Size"))
				{
					showGridWindow = !showGridWindow;
				}
				EndMenu();
			}
			Separator();
			if (MenuItem("Show Mouse Coord", nullptr, showMouseCoord))
			{
				showMouseCoord = !showMouseCoord;
			}
			Separator();
			if (BeginMenu("Skin"))
			{
				if (MenuItem("Next"))
				{
					// TODO
				}
				if (MenuItem("Previous"))
				{
					// TODO
				}
				Separator();
				if (MenuItem("Choose"))
				{
					showSkin = true;
				}
				EndMenu();
			}

			EndMenu();
		}
		if (BeginMenu("Player", showGameWindow))
		{
			if (MenuItem("Dot Kid", nullptr, PlayerMgr.dotkid))
			{
				PlayerMgr.dotkid = !PlayerMgr.dotkid;
			}
			if (MenuItem("Outline", nullptr, PlayerMgr.dotkidOutline, PlayerMgr.dotkid))
			{
				PlayerMgr.dotkidOutline = !PlayerMgr.dotkidOutline;
			}
			Separator();
			if (MenuItem("Enable Death", nullptr, PlayerMgr.deathEnable))
			{
				PlayerMgr.deathEnable = !PlayerMgr.deathEnable;
			}
			if (MenuItem("Inf Jump", nullptr, PlayerMgr.infjump))
			{
				PlayerMgr.infjump = !PlayerMgr.infjump;
			}
			Separator();
			if (BeginMenu("Save Type"))
			{
				if (MenuItem("Only Shoot", nullptr, PlayerMgr.saveType == SaveType::OnlyShoot))
				{
					PlayerMgr.saveType = SaveType::OnlyShoot;
				}
				if (MenuItem("Shoot Or Bullet", nullptr, PlayerMgr.saveType == SaveType::ShootOrBullet))
				{
					PlayerMgr.saveType = SaveType::ShootOrBullet;
				}
				EndMenu();
			}
			if (BeginMenu("Map Border Type"))
			{
				if (MenuItem("Killer", nullptr, PlayerMgr.deathBorder == DeathBorder::Killer))
				{
					PlayerMgr.deathBorder = DeathBorder::Killer;
				}
				if (MenuItem("Solid", nullptr, PlayerMgr.deathBorder == DeathBorder::Solid))
				{
					PlayerMgr.deathBorder = DeathBorder::Solid;
				}
				EndMenu();
			}
			Separator();
			if (BeginMenu("Mask (Hitbox)", !PlayerMgr.dotkid))
			{
				if (MenuItem("Only Player", nullptr, PlayerMgr.showMask == ShowMask::OnlyPlayer))
				{
					PlayerMgr.showMask = ShowMask::OnlyPlayer;
				}
				if (MenuItem("Only Mask", nullptr, PlayerMgr.showMask == ShowMask::OnlyMask))
				{
					PlayerMgr.showMask = ShowMask::OnlyMask;
				}
				if (MenuItem("Player And Mask", nullptr, PlayerMgr.showMask == ShowMask::PlayerAndMask))
				{
					PlayerMgr.showMask = ShowMask::PlayerAndMask;
				}
				EndMenu();
			}
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
			if (MenuItem("Shift", nullptr, showShift))
			{
				showShift = !showShift;
			}
			EndMenu();
		}
		if (BeginMenu("Help"))
		{
			if (MenuItem("Github"))
			{
				//Win::ShellExecuteA(nullptr, "open", "https://github.com/cubeww/imjtool", nullptr, nullptr, 10);
			}
			Separator();
			if (MenuItem("About"))
			{
				showAbout = true;
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
		if (!Gm.editor.mouseInTitle)
			flag |= ImGuiWindowFlags_NoMove;
		if (Begin("Game Window", &showGameWindow, flag))
		{
			auto cursorStartPos = GetCursorStartPos();
			auto windowPos = GetWindowPos();
			Image(*Gm.gameTexture);
			Gm.editor.update();

			if (showGrid)
			{
				SetCursorPos(GetCursorStartPos());
				auto col = sf::Color::Black;
				col.a = 66;
				Image(*gridTexture, col);
			}
			if (showMouseCoord)
			{
				auto pos = ImVec2(GetMousePos().x - windowPos.x - cursorStartPos.x, GetMousePos().y - windowPos.y - cursorStartPos.y);
				if (pos.x >= 0 && pos.x <= 800 && pos.y >= 0 && pos.y <= 608)
				{
					BeginTooltip();
					auto coord = "(" + to_string(FloorToInt(pos.x)) + ", " + to_string(FloorToInt(pos.y)) + ")";
					Text(coord.data());
					EndTooltip();
				}
			}
			End();
		}
	}
	if (showPalette)
	{
		SetNextWindowSize(ImVec2(200, 300), ImGuiCond_Once);
		if (Begin("Palette", &showPalette))
		{
			auto addObject = [&](int index, string hint = "")
			{
				auto name = spriteOf(index);
				if (paletteIcons[index] == nullptr)
				{
					shared_ptr<sf::Sprite> spr = SkinMgr.getCurrentSprite(name)->items[0]->sprite;
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
					Gm.editor.selectIndex = index;
				}
				if (hint != "" && IsItemHovered())
				{
					BeginTooltip();
					Text(hint.data());
					EndTooltip();
				}
			};
			if (CollapsingHeader("Player"))
			{
				addObject(GetIndex(PlayerStart));
				SameLine();
				addObject(GetIndex(Save));
				SameLine();
				addObject(GetIndex(Warp));
			}
			if (CollapsingHeader("Killer"))
			{
				addObject(GetIndex(SpikeUp));
				SameLine();
				addObject(GetIndex(SpikeDown));
				SameLine();
				addObject(GetIndex(SpikeLeft));
				SameLine();
				addObject(GetIndex(SpikeRight));

				addObject(GetIndex(MiniSpikeUp));
				SameLine();
				addObject(GetIndex(MiniSpikeDown));
				SameLine();
				addObject(GetIndex(MiniSpikeLeft));
				SameLine();
				addObject(GetIndex(MiniSpikeRight));

				addObject(GetIndex(Apple));
				SameLine();
				addObject(GetIndex(KillerBlock));
			}
			if (CollapsingHeader("Block & Platform"))
			{
				addObject(GetIndex(Block));
				SameLine();
				addObject(GetIndex(MiniBlock));
				SameLine();
				addObject(GetIndex(Platform));
				SameLine();
				addObject(GetIndex(BulletBlocker));
				
			}
			if (CollapsingHeader("Vine & Water"))
			{
				addObject(GetIndex(WalljumpR));
				SameLine();
				addObject(GetIndex(WalljumpL));

				addObject(GetIndex(Water), "Water 1 (Refresh Jump, High)");
				SameLine();
				addObject(GetIndex(Water2), "Water 2 (No Refresh Jump)");
				SameLine();
				addObject(GetIndex(Water3), "Water 3 (Refresh Jump)");
			}
			if (CollapsingHeader("Misc"))
			{
				addObject(GetIndex(GravityArrowUp));
				SameLine();
				addObject(GetIndex(GravityArrowDown));
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
			debugValue("FPS", Gm.fps);
			debugValue("Inst", ObjMgr.objects.size());
			debugValue("Texture Count", ResMgr.textures.size());
			debugValue("Sprite Count", ResMgr.sprites.size());
			debugValue("Undo Stack Size", Gm.editor.undoEvents.size());
			debugValue("Undo Pos", Gm.editor.undoPos);
			if (Button("DEL Instances"))
			{
				DestroyAll();
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
	gridWindow();
	skinWindow();
}

void Gui::aboutWindow()
{
	if (showAbout)
	{
		OpenPopup("About");
	}

	SetNextWindowSize(ImVec2(420, 420), ImGuiCond_Once);
	if (BeginPopupModal("About", &showAbout))
	{
		Text("Immediate Mode Jump Tool");
		Text("By Cube");
		Text("Powered By:");
		Image(*ResMgr.textures["sfml"]);
		Text("Simple and Fast Multimedia Library");
		Image(*ResMgr.textures["imgui"]);
		Text("Dear ImGui");
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
		if (Begin("Shift Objects", &showShift))
		{
			InputInt("Shift X", &shiftX);
			InputInt("Shift Y", &shiftY);

			SetCursorPos(ImVec2(48, GetCursorPos().y));

			if (Button("U", ImVec2(32, 32)))
			{
				for (auto const& i : ObjMgr.objects)
				{
					if (i->index == GetIndex(Player))
						continue;
					Gm.editor.addMoveEvent(i, i->x, i->y, i->x, i->y - shiftY);
					i->y -= shiftY;
				}
				Gm.editor.finishEvent();
			}
			if (Button("L", ImVec2(32, 32)))
			{
				for (auto const& i : ObjMgr.objects)
				{
					if (i->index == GetIndex(Player))
						continue;
					Gm.editor.addMoveEvent(i, i->x, i->y, i->x - shiftX, i->y);
					i->x -= shiftX;
				}
				Gm.editor.finishEvent();
			}
			SameLine();
			if (Button("D", ImVec2(32, 32)))
			{
				for (auto const& i : ObjMgr.objects)
				{
					if (i->index == GetIndex(Player))
						continue;
					Gm.editor.addMoveEvent(i, i->x, i->y, i->x, i->y + shiftY);
					i->y += shiftY;
				}
				Gm.editor.finishEvent();
			}
			SameLine();
			if (Button("R", ImVec2(32, 32)))
			{
				for (auto const& i : ObjMgr.objects)
				{
					if (i->index == GetIndex(Player))
						continue;
					Gm.editor.addMoveEvent(i, i->x, i->y, i->x + shiftX, i->y);
					i->x += shiftX;
				}
				Gm.editor.finishEvent();
			}

			End();
		}
	}
}

void Gui::gridWindow()
{
	if (showGridWindow)
	{
		OpenPopup("Set Grid");
	}

	SetNextWindowSize(ImVec2(200, 100), ImGuiCond_Once);
	if (BeginPopupModal("Set Grid", &showGridWindow))
	{
		InputInt("Grid W", &gridW);
		InputInt("Grid H", &gridH);

		gridW = clamp(gridW, 1, 800);
		gridH = clamp(gridH, 1, 608);

		if (Button("OK"))
		{
			updateGrid();
			showGridWindow = false;
			CloseCurrentPopup();
		}
		EndPopup();
	}
}

void Gui::updateGrid()
{
	if (gridTexture == nullptr)
	{
		gridTexture = make_shared<sf::RenderTexture>();
		gridTexture->create(800, 608);
	}
	gridTexture->clear(sf::Color::Transparent);
	for (auto yy = 0; yy <= 608; yy += gridH)
	{
		sf::RectangleShape rect;
		rect.setFillColor(sf::Color::Black);
		rect.setPosition(0, static_cast<float>(yy));
		rect.setSize(sf::Vector2f(800, 1));
		gridTexture->draw(rect);
	}
	for (auto xx = 0; xx <= 800; xx += gridW)
	{
		sf::RectangleShape rect;
		rect.setFillColor(sf::Color::Black);
		rect.setPosition(static_cast<float>(xx), 0);
		rect.setSize(sf::Vector2f(1, 608));
		gridTexture->draw(rect);
	}
}

void Gui::skinWindow()
{
	if (showSkin)
	{
		OpenPopup("Skin");
	}

	SetNextWindowSize(ImVec2(430, 330), ImGuiCond_Once);
	if (BeginPopupModal("Skin", &showSkin))
	{
		Columns(2);
		Text("Search");
		SameLine();
		if (InputText("##SearchSkin", &skinSearchStr))
		{
			skinSearchVec.clear();
			int index = 0;
			for (auto name : SkinMgr.skinNames)
			{
				if (name.find(skinSearchStr))
				{
					skinSearchVec.push_back(index);
				}
				index++;
			}
		}
		if (BeginListBox("##Skins", ImVec2(200, 250)))
		{
			int index = 0;
			for (auto const& name : SkinMgr.skinNames)
			{
				if (find(skinSearchVec.begin(), skinSearchVec.end(), index) != skinSearchVec.end())
				{
					index++;
					continue;
				}
				if (Selectable(name.data(), skinSelect == index) || SkinMgr.previewSkin == nullptr)
				{
					skinSelect = index;
					SkinMgr.previewSkin = make_shared<SkinPackage>(name);
				}

				index++;
			}
			EndListBox();
		}
		NextColumn();
		Text("Preview:");

		auto startPos = GetCursorPos();
		auto drawPreview = [&](int index, int xx, int yy)
		{
			auto name = spriteOf(index);
			SetCursorPos(ImVec2(startPos.x + xx, startPos.y + yy));

			auto obj = SkinMgr.getPreview(name);
			if (obj != nullptr)
			{
				Image(*obj->sprite->items[0]->sprite);
			}
			else
			{
				Image(*ResMgr.sprites[name]->items[0]->sprite);
			}
		};
		auto d = 32;
		drawPreview(GetIndex(Warp), 0, 0);
		drawPreview(GetIndex(SpikeUp), d, 0);
		drawPreview(GetIndex(JumpRefresher), d * 2, 0);
		drawPreview(GetIndex(Block), d * 3, 0);
		drawPreview(GetIndex(WalljumpR), d * 3, 0);
		drawPreview(GetIndex(Block), d * 4, 0);
		drawPreview(GetIndex(WalljumpL), d * 4, 0);

		drawPreview(GetIndex(SpikeLeft), 0, d);
		drawPreview(GetIndex(Block), d, d);
		drawPreview(GetIndex(SpikeRight), d * 2, d);
		drawPreview(GetIndex(Platform), d * 3, d);
		drawPreview(GetIndex(Apple), d * 4, d);

		drawPreview(GetIndex(PlayerStart), 0, d * 2);
		drawPreview(GetIndex(SpikeDown), d, d * 2);
		drawPreview(GetIndex(MiniSpikeUp), d * 2, d * 2);
		drawPreview(GetIndex(MiniSpikeRight), d * 2 + 16, d * 2);
		drawPreview(GetIndex(MiniSpikeLeft), d * 2, d * 2 + 16);
		drawPreview(GetIndex(MiniSpikeDown), d * 2 + 16, d * 2 + 16);
		drawPreview(GetIndex(Water2), d * 3, d * 2);
		drawPreview(GetIndex(Save), d * 4, d * 2);

		Columns();
		if (Button("Apply"))
		{
			SkinMgr.apply(SkinMgr.previewSkin);
			showSkin = false;
		}
		SameLine();
		if (Button("Cancel"))
		{
			showSkin = false;
		}
		EndPopup();
	}

}
