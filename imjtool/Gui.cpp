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
			auto addObjectWithSkin = [&](int index, shared_ptr<SkinObject> sprite, shared_ptr<SkinObject> defsprite, string hint = "")
			{
				if (SkinMgr.curSkin == nullptr || !sprite->valid)
					sprite = std::move(defsprite);

				if (paletteIcons[index] == nullptr)
				{
					auto spr = sprite->sprite->items[0]->sprite;
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
					Gm.editor.selectSprite = sprite->sprite;
				}
				if (hint != "" && IsItemHovered())
				{
					BeginTooltip();
					Text(hint.data());
					EndTooltip();
				}
			};
			auto addObject = [&](int index, shared_ptr<Sprite> sprite, string hint = "")
			{
				if (paletteIcons[index] == nullptr)
				{
					auto spr = sprite->items[0]->sprite;
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
					Gm.editor.selectSprite = sprite;
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
				addObjectWithSkin(GetIndex(PlayerStart), SkinMgr.curSkin->playerStart, SkinMgr.defaultSkin->playerStart);
				SameLine();
				addObjectWithSkin(GetIndex(Save), SkinMgr.curSkin->save, SkinMgr.defaultSkin->save);
				SameLine();
				addObjectWithSkin(GetIndex(Warp), SkinMgr.curSkin->warp, SkinMgr.defaultSkin->warp);
			}
			if (CollapsingHeader("Killer"))
			{
				addObjectWithSkin(GetIndex(SpikeUp), SkinMgr.curSkin->spikeUp, SkinMgr.defaultSkin->spikeUp);
				SameLine();
				addObjectWithSkin(GetIndex(SpikeDown), SkinMgr.curSkin->spikeDown, SkinMgr.defaultSkin->spikeDown);
				SameLine();
				addObjectWithSkin(GetIndex(SpikeLeft), SkinMgr.curSkin->spikeLeft, SkinMgr.defaultSkin->spikeLeft);
				SameLine();
				addObjectWithSkin(GetIndex(SpikeRight), SkinMgr.curSkin->spikeRight, SkinMgr.defaultSkin->spikeRight);

				addObjectWithSkin(GetIndex(MiniSpikeUp), SkinMgr.curSkin->miniSpikeUp, SkinMgr.defaultSkin->miniSpikeUp);
				SameLine();
				addObjectWithSkin(GetIndex(MiniSpikeDown), SkinMgr.curSkin->miniSpikeDown, SkinMgr.defaultSkin->miniSpikeDown);
				SameLine();
				addObjectWithSkin(GetIndex(MiniSpikeLeft), SkinMgr.curSkin->miniSpikeLeft, SkinMgr.defaultSkin->miniSpikeLeft);
				SameLine();
				addObjectWithSkin(GetIndex(MiniSpikeRight), SkinMgr.curSkin->miniSpikeRight, SkinMgr.defaultSkin->miniSpikeRight);

				addObjectWithSkin(GetIndex(Apple), SkinMgr.curSkin->apple, SkinMgr.defaultSkin->apple);
				SameLine();
				addObjectWithSkin(GetIndex(KillerBlock), SkinMgr.curSkin->killerBlock, SkinMgr.defaultSkin->killerBlock);
			}
			if (CollapsingHeader("Block & Platform"))
			{
				addObjectWithSkin(GetIndex(Block), SkinMgr.curSkin->block, SkinMgr.defaultSkin->block);
				SameLine();
				addObjectWithSkin(GetIndex(MiniBlock), SkinMgr.curSkin->miniBlock, SkinMgr.defaultSkin->miniBlock);
				SameLine();
				addObjectWithSkin(GetIndex(Platform), SkinMgr.curSkin->platform, SkinMgr.defaultSkin->platform);
			}
			if (CollapsingHeader("Vine & Water"))
			{
				addObjectWithSkin(GetIndex(WalljumpR), SkinMgr.curSkin->walljumpR, SkinMgr.defaultSkin->walljumpR);
				SameLine();
				addObjectWithSkin(GetIndex(WalljumpL), SkinMgr.curSkin->walljumpL, SkinMgr.defaultSkin->walljumpL);

				addObjectWithSkin(GetIndex(Water), SkinMgr.curSkin->water, SkinMgr.defaultSkin->water, "Water 1 (Refresh Jump, High)");
				SameLine();
				addObjectWithSkin(GetIndex(Water2), SkinMgr.curSkin->water2, SkinMgr.defaultSkin->water2, "Water 2 (No Refresh Jump)");
				SameLine();
				addObjectWithSkin(GetIndex(Water3), SkinMgr.curSkin->water3, SkinMgr.defaultSkin->water3, "Water 3 (Refresh Jump)");
			}
			if (CollapsingHeader("Misc"))
			{
				addObject(GetIndex(GravityArrowUp), ResMgr.sprites["gravity_up"]);
				SameLine();
				addObject(GetIndex(GravityArrowDown), ResMgr.sprites["gravity_down"]);
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
		auto drawPreview = [&](shared_ptr<SkinObject> obj, shared_ptr<SkinObject> def, int xx, int yy)
		{
			SetCursorPos(ImVec2(startPos.x + xx, startPos.y + yy));
			if (obj->valid)
			{
				obj->sprite->items[0]->sprite->setOrigin(0, 0);
				obj->sprite->items[0]->sprite->setPosition(0, 0);
				Image(*obj->sprite->items[0]->sprite);
			}
			else
			{
				def->sprite->items[0]->sprite->setOrigin(0, 0);
				def->sprite->items[0]->sprite->setPosition(0, 0);
				Image(*def->sprite->items[0]->sprite);
			}
		};
		auto d = 32;
		drawPreview(SkinMgr.previewSkin->warp, SkinMgr.defaultSkin->warp, 0, 0);
		drawPreview(SkinMgr.previewSkin->spikeUp, SkinMgr.defaultSkin->spikeUp, d, 0);
		drawPreview(SkinMgr.previewSkin->jumpRefresher, SkinMgr.defaultSkin->jumpRefresher, d * 2 + 8, 8);
		drawPreview(SkinMgr.previewSkin->block, SkinMgr.defaultSkin->block, d * 3, 0);
		drawPreview(SkinMgr.previewSkin->walljumpR, SkinMgr.defaultSkin->walljumpR, d * 3, 0);
		drawPreview(SkinMgr.previewSkin->block, SkinMgr.defaultSkin->block, d * 4, 0);
		drawPreview(SkinMgr.previewSkin->walljumpL, SkinMgr.defaultSkin->walljumpL, d * 4, 0);

		drawPreview(SkinMgr.previewSkin->spikeLeft, SkinMgr.defaultSkin->spikeLeft, 0, d);
		drawPreview(SkinMgr.previewSkin->block, SkinMgr.defaultSkin->block, d, d);
		drawPreview(SkinMgr.previewSkin->spikeRight, SkinMgr.defaultSkin->spikeRight, d * 2, d);
		drawPreview(SkinMgr.previewSkin->platform, SkinMgr.defaultSkin->platform, d * 3, d);
		drawPreview(SkinMgr.previewSkin->apple, SkinMgr.defaultSkin->apple, d * 4, d);

		drawPreview(SkinMgr.previewSkin->playerStart, SkinMgr.defaultSkin->playerStart, 0, d * 2);
		drawPreview(SkinMgr.previewSkin->spikeDown, SkinMgr.defaultSkin->spikeDown, d, d * 2);
		drawPreview(SkinMgr.previewSkin->miniSpikeUp, SkinMgr.defaultSkin->miniSpikeUp, d * 2, d * 2);
		drawPreview(SkinMgr.previewSkin->miniSpikeRight, SkinMgr.defaultSkin->miniSpikeRight, d * 2 + 16, d * 2);
		drawPreview(SkinMgr.previewSkin->miniSpikeLeft, SkinMgr.defaultSkin->miniSpikeLeft, d * 2, d * 2 + 16);
		drawPreview(SkinMgr.previewSkin->miniSpikeDown, SkinMgr.defaultSkin->miniSpikeDown, d * 2 + 16, d * 2 + 16);
		drawPreview(SkinMgr.previewSkin->water2, SkinMgr.defaultSkin->water2, d * 3, d * 2);
		drawPreview(SkinMgr.previewSkin->save, SkinMgr.defaultSkin->save, d * 4, d * 2);

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
