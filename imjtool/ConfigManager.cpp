#include "ConfigManager.h"

#include <fstream>
#include <filesystem>

#include "json.hpp"
#include "Game.h"

void ConfigManager::save()
{
	if (SkinMgr.curSkin)
		curConfig["skin"] = SkinMgr.curSkin->skinName;

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
		SkinMgr.apply(make_shared<SkinPackage>(curConfig["skin"]));
}
