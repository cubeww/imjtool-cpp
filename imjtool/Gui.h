#pragma once

#include <map>
#include <memory>

#include "imgui.h"

namespace sf
{
	class RenderTexture;
}

using namespace ImGui;

class Gui
{
public:
	void update();

private:
	bool showGameWindow = true;
	bool showPalette = true;

	std::map<int, std::shared_ptr<sf::RenderTexture>> paletteIcons;

	void mainMenu();
	void gameWindow();
};
