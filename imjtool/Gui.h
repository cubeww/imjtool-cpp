#pragma once

#include <map>
#include <iostream>
#include <vector>

#include "imgui.h"

namespace sf
{
	class RenderTexture;
}

using namespace std;

enum class ThemeName
{
	Default,
	Dark,
	Light,
	Diana,
};

class Gui
{
public:
	void update();

	bool showGameWindow = true;
	bool showPalette = true;

	bool showDebug = false;
	int debugSpriteCount = 0;

	bool showAbout = false;
	bool showShift = false;

	bool showSnap = false;
	int snapW = 32;
	int snapH = 32;

	ThemeName curTheme = ThemeName::Default;
	void setGuiTheme(ThemeName name);

	bool showSkin = false;
	int skinSelect = 0;
	string skinSearchStr;
	vector<int> skinSearchVec;

	bool showGrid = false;
	int gridW = 32;
	int gridH = 32;
	bool showGridWindow = false;
	bool showMouseCoord = false;
	shared_ptr<sf::RenderTexture> gridTexture;

	int shiftX = 32;
	int shiftY = 32;

	std::map<int, std::shared_ptr<sf::RenderTexture>> paletteIcons;

	void updateGrid();
};
