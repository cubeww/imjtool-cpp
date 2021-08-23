#pragma once

#include <map>
#include <iostream>

#include "imgui.h"

namespace sf
{
	class RenderTexture;
}

using namespace ImGui;
using namespace std;

class Gui
{
public:
	void update();

private:
	bool showGameWindow = true;
	bool showPalette = true;
	bool showDebug = true;
	bool showAbout = false;
	bool showShift = false;
	bool showSkin = false;

	bool showGrid = false;
	int gridW = 32;
	int gridH = 32;
	bool showGridWindow = false;
	bool showMouseCoord = false;
	shared_ptr<sf::RenderTexture> gridTexture;

	int shiftX = 32;
	int shiftY = 32;

	std::map<int, std::shared_ptr<sf::RenderTexture>> paletteIcons;

	void mainMenu();
	void gameWindow();
	void debugWindow();
	void aboutWindow();
	void shiftWindow();
	void gridWindow();
	void skinWindow();

	void updateGrid();
};
