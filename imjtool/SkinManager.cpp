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

	auto addObject = [&](int index, string filename, int xnum = 1, int ynum = 1, float speed = NAN, bool tile = true)
	{
		auto name = spriteOf(index);
		if (filesystem::exists(filename))
		{
			objects[name] = make_shared<SkinObject>(filename, xnum, ynum, speed);
		}
	};

	addObject(GetIndex(SpikeUp), path + "spikeup.png", spikeFrames, 1, spikeSpeed);
	addObject(GetIndex(SpikeDown), path + "spikedown.png", spikeFrames, 1, spikeSpeed);
	addObject(GetIndex(SpikeLeft), path + "spikeleft.png", spikeFrames, 1, spikeSpeed);
	addObject(GetIndex(SpikeRight), path + "spikeright.png", spikeFrames, 1, spikeSpeed);

	addObject(GetIndex(MiniSpikeUp), path + "miniup.png", miniSpikeFrames, 1, miniSpikeSpeed);
	addObject(GetIndex(MiniSpikeDown), path + "minidown.png", miniSpikeFrames, 1, miniSpikeSpeed);
	addObject(GetIndex(MiniSpikeLeft), path + "minileft.png", miniSpikeFrames, 1, miniSpikeSpeed);
	addObject(GetIndex(MiniSpikeRight), path + "miniright.png", miniSpikeFrames, 1, miniSpikeSpeed);

	addObject(GetIndex(Apple), path + "apple.png", 2, 1);
	addObject(GetIndex(KillerBlock), path + "killerblock.png");

	addObject(GetIndex(Block), path + "block.png");
	addObject(GetIndex(MiniBlock), path + "miniblock.png");
	addObject(GetIndex(BulletBlocker), path + "bulletblocker.png");
	addObject(GetIndex(Platform), path + "platform.png");

	addObject(GetIndex(WalljumpL), path + "walljumpL.png");
	addObject(GetIndex(WalljumpR), path + "walljumpR.png");
	addObject(GetIndex(Water), path + "water1.png");
	addObject(GetIndex(Water2), path + "water2.png");
	addObject(GetIndex(Water3), path + "water3.png");

	addObject(GetIndex(Warp), path + "warp.png");
	addObject(GetIndex(PlayerStart), path + "playerstart.png");
	addObject(GetIndex(JumpRefresher), path + "jumprefresher.png");

	addObject(GetIndex(Save), path + "save.png", 2, 1);

	addObject(GetIndex(Bg), path + "bg.png", 1, 1, 0, bgType == BgType::Tile);
}

SkinObject::SkinObject(string filename, int xnum, int ynum, float speed, bool tile)
{
	auto tex = make_shared<sf::Texture>();
	tex->loadFromFile(filename);
	tex->setRepeated(tile);

	auto spr = make_shared<Sprite>();
	spr->addSheet(tex, xnum, ynum, false);

	texture = tex;
	sprite = spr;
	this->speed = speed;
}
void SkinManager::apply(shared_ptr<SkinPackage> package)
{
	curSkin = package;

	for (auto i : ObjMgr.objects)
	{
		if (isSkinable(i->index))
		{
			i->applySkin();

			if (i->index == GetIndex(Bg))
			{
				i->x = 0;
				i->y = 0;
			}
		}
	}

	Gm.gui.paletteIcons.clear();
}

shared_ptr<SkinObject> SkinManager::getCurrent(string name)
{
	if (curSkin != nullptr) {
		if (curSkin->objects.contains(name))
		{
			return curSkin->objects[name];
		}
	}
	return nullptr;
}

shared_ptr<Sprite> SkinManager::getCurrentSprite(string name)
{
	if (curSkin != nullptr) {
		if (curSkin->objects.contains(name))
		{
			return curSkin->objects[name]->sprite;
		}
	}
	return ResMgr.sprites[name];
}

shared_ptr<SkinObject> SkinManager::getPreview(string name)
{
	if (previewSkin->objects.contains(name))
	{
		return previewSkin->objects[name];
	}
	return nullptr;
}
