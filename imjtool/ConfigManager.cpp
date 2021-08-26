#include "ConfigManager.h"

#include <fstream>
#include <filesystem>

#include "json.hpp"
#include "Game.h"

void ConfigManager::save()
{
	curConfig["skin"] = SkinMgr.curSkin->skinName;
	curConfig["theme"] = Gm.gui.curTheme;

	ofstream file("config.json");
	file << curConfig;
	file.close();
}

void ConfigManager::load()
{
	if (!filesystem::exists("config.json"))
		return;

	ifstream file("config.json");
	file >> curConfig;
	file.close();

	if (curConfig.contains("skin"))
		SkinMgr.apply(curConfig["skin"]);

	if (curConfig.contains("theme"))
		Gm.gui.setGuiTheme(curConfig["theme"]);
}
