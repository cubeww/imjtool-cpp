#pragma once

#include "imgui.h"

using namespace ImGui;

class Gui
{
public:
	void update();

private:
	bool showGameWindow = true;
	bool showPalette = true;

	void mainMenu();
	void gameWindow();
};
