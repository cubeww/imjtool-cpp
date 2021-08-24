#include "SkinManager.h"
#include "ini.h"
#include <sstream>
#include "Sprite.h"
#include <filesystem>
#include "Game.h"
#include "InGame.h"

using namespace mINI;

void SkinManager::loadConfig()
{
	INIFile inifile("skins/skins.ini");
	INIStructure ini;
	inifile.read(ini);

	string names = ini["skins"]["names"];
	istringstream ss(names);
	string name;

	while (getline(ss, name, ','))
	{
		skinNames.push_back(name);
	}
}

void SkinManager::loadDefault()
{
	defaultSkin = make_shared<SkinPackage>();
	curSkin = make_shared<SkinPackage>();
}

SkinPackage::SkinPackage()
{
	// create default skin package
	bgType = BgType::Stretch;

	hspeed = 0;
	vspeed = 0;

	spikeUp = make_shared<SkinObject>(ResMgr.sprites["spike_up"]);
	spikeDown = make_shared<SkinObject>(ResMgr.sprites["spike_down"]);
	spikeLeft = make_shared<SkinObject>(ResMgr.sprites["spike_left"]);
	spikeRight = make_shared<SkinObject>(ResMgr.sprites["spike_right"]);

	miniSpikeUp = make_shared<SkinObject>(ResMgr.sprites["mini_spike_up"]);
	miniSpikeDown = make_shared<SkinObject>(ResMgr.sprites["mini_spike_down"]);
	miniSpikeLeft = make_shared<SkinObject>(ResMgr.sprites["mini_spike_left"]);
	miniSpikeRight = make_shared<SkinObject>(ResMgr.sprites["mini_spike_right"]);

	apple = make_shared<SkinObject>(ResMgr.sprites["apple"]);
	killerBlock = make_shared<SkinObject>(ResMgr.sprites["killer_block"]);

	block = make_shared<SkinObject>(ResMgr.sprites["block"]);
	miniBlock = make_shared<SkinObject>(ResMgr.sprites["mini_block"]);
	bulletBlocker = make_shared<SkinObject>(ResMgr.sprites["bullet_blocker"]);
	platform = make_shared<SkinObject>(ResMgr.sprites["platform"]);

	walljumpL = make_shared<SkinObject>(ResMgr.sprites["walljump_l"]);
	walljumpR = make_shared<SkinObject>(ResMgr.sprites["walljump_r"]);
	water = make_shared<SkinObject>(ResMgr.sprites["water"]);
	water2 = make_shared<SkinObject>(ResMgr.sprites["water2"]);
	water3 = make_shared<SkinObject>(ResMgr.sprites["water3"]);

	warp = make_shared<SkinObject>(ResMgr.sprites["warp"]);
	playerStart = make_shared<SkinObject>(ResMgr.sprites["player_start"]);
	jumpRefresher = make_shared<SkinObject>(ResMgr.sprites["jump_refresher"]);

	save = make_shared<SkinObject>(ResMgr.sprites["save"]);
}

SkinPackage::SkinPackage(string name)
{
	auto path = "skins/" + name + "/";
	INIFile inifile(path + "skin_config.ini");
	INIStructure ini;
	inifile.read(ini);

	auto readInt = [&](string section, string key, int def)
	{
		if (ini.has(section) && ini[section].has(key))
		{
			return stoi(ini[section][key]);
		}
		return def;
	};

	auto readFloat = [&](string section, string key, float def)
	{
		if (ini.has(section) && ini[section].has(key))
		{
			return stof(ini[section][key]);
		}
		return def;
	};

	auto read = [&](string section, string key, string def)
	{
		if (ini.has(section) && ini[section].has(key))
		{
			return ini[section][key];
		}
		return def;
	};

	int spikeFrames = readInt("objects", "spike_frames", 1);
	float spikeSpeed = readFloat("objects", "spike_animspeed", 1);

	int miniSpikeFrames = readInt("objects", "minispike_frames", 1);
	float miniSpikeSpeed = readFloat("objects", "minispike_animspeed", 1);

	auto bgtype = read("bg", "type", "tile");

	if (bgtype == "stretch") bgType = BgType::Stretch;
	else bgType = BgType::Tile;

	hspeed = readFloat("bg", "hspeed", 0);
	vspeed = readFloat("bg", "vspeed", 0);

	spikeUp = make_shared<SkinObject>(path + "spikeup.png", spikeFrames, 1, spikeSpeed);
	spikeDown = make_shared<SkinObject>(path + "spikedown.png", spikeFrames, 1, spikeSpeed);
	spikeLeft = make_shared<SkinObject>(path + "spikeleft.png", spikeFrames, 1, spikeSpeed);
	spikeRight = make_shared<SkinObject>(path + "spikeright.png", spikeFrames, 1, spikeSpeed);

	miniSpikeUp = make_shared<SkinObject>(path + "miniup.png", miniSpikeFrames, 1, miniSpikeSpeed);
	miniSpikeDown = make_shared<SkinObject>(path + "minidown.png", miniSpikeFrames, 1, miniSpikeSpeed);
	miniSpikeLeft = make_shared<SkinObject>(path + "minileft.png", miniSpikeFrames, 1, miniSpikeSpeed);
	miniSpikeRight = make_shared<SkinObject>(path + "miniright.png", miniSpikeFrames, 1, miniSpikeSpeed);

	apple = make_shared<SkinObject>(path + "apple.png", 2, 1);
	killerBlock = make_shared<SkinObject>(path + "killerblock.png");

	block = make_shared<SkinObject>(path + "block.png");
	miniBlock = make_shared<SkinObject>(path + "miniblock.png");
	bulletBlocker = make_shared<SkinObject>(path + "bulletblocker.png");
	platform = make_shared<SkinObject>(path + "platform.png");

	walljumpL = make_shared<SkinObject>(path + "walljumpL.png");
	walljumpR = make_shared<SkinObject>(path + "walljumpR.png");
	water = make_shared<SkinObject>(path + "water1.png");
	water2 = make_shared<SkinObject>(path + "water2.png");
	water3 = make_shared<SkinObject>(path + "water3.png");

	warp = make_shared<SkinObject>(path + "warp.png");
	playerStart = make_shared<SkinObject>(path + "playerstart.png");
	jumpRefresher = make_shared<SkinObject>(path + "jumprefresher.png");

	save = make_shared<SkinObject>(path + "save.png", 2, 1);
}

SkinObject::SkinObject(string filename, int xnum, int ynum, float speed)
{
	if (filesystem::exists(filename)) 
	{
		auto tex = make_shared<sf::Texture>();
		tex->loadFromFile(filename);

		auto spr = make_shared<Sprite>();
		spr->addSheet(tex, xnum, ynum, false);

		texture = tex;
		sprite = spr;
		this->speed = speed;

		valid = true;
	}
	else
	{
		valid = false;
	}
}

SkinObject::SkinObject(shared_ptr<Sprite> sprite, float speed)
{
	texture = nullptr;
	this->sprite = sprite;
	this->speed = speed;

	valid = true;
}

void SkinManager::apply(shared_ptr<SkinPackage> package)
{
	curSkin = package;

	for (auto i : ObjMgr.objects)
	{
		if (inPalette(i->index))
		{
			i->applySkin();
		}
	}

	Gm.gui.paletteIcons.clear();
}
