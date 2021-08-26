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
	this->skinName = name;
	auto path = "skins/" + name + "/";
	INIFile inifile(path + "skin_config.ini");
	INIStructure ini;
	inifile.read(ini);
	cout << name << endl;
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

	auto bgtype = read("bg", "type", "stretch");

	if (bgtype == "stretch")
	{
		bgType = BgType::Stretch;
	}
	else
	{
		bgType = BgType::Tile;
	}

	hspeed = readFloat("bg", "hspeed", 0);
	vspeed = readFloat("bg", "vspeed", 0);

	auto addObject = [&](int index, string filename, int xo, int yo, int xnum = 1, int ynum = 1, float speed = NAN, bool tile = true)
	{
		auto name = spriteOf(index);
		if (filesystem::exists(filename))
		{
			objects[name] = make_shared<SkinObject>(filename, xo, yo, xnum, ynum, speed);
		}
	};

	addObject(GetIndex(SpikeUp), path + "spikeup.png", 0, 0, spikeFrames, 1, spikeSpeed);
	addObject(GetIndex(SpikeDown), path + "spikedown.png", 0, 0, spikeFrames, 1, spikeSpeed);
	addObject(GetIndex(SpikeLeft), path + "spikeleft.png", 0, 0, spikeFrames, 1, spikeSpeed);
	addObject(GetIndex(SpikeRight), path + "spikeright.png", 0, 0, spikeFrames, 1, spikeSpeed);

	addObject(GetIndex(MiniSpikeUp), path + "miniup.png", 0, 0, miniSpikeFrames, 1, miniSpikeSpeed);
	addObject(GetIndex(MiniSpikeDown), path + "minidown.png", 0, 0, miniSpikeFrames, 1, miniSpikeSpeed);
	addObject(GetIndex(MiniSpikeLeft), path + "minileft.png", 0, 0, miniSpikeFrames, 1, miniSpikeSpeed);
	addObject(GetIndex(MiniSpikeRight), path + "miniright.png", 0, 0, miniSpikeFrames, 1, miniSpikeSpeed);

	addObject(GetIndex(Apple), path + "apple.png", 10, 12, 2, 1);
	addObject(GetIndex(KillerBlock), path + "killerblock.png", 0, 0);

	addObject(GetIndex(Block), path + "block.png", 0, 0);
	addObject(GetIndex(MiniBlock), path + "miniblock.png", 0, 0);
	addObject(GetIndex(BulletBlocker), path + "bulletblocker.png", 0, 0);
	addObject(GetIndex(Platform), path + "platform.png", 0, 0);

	addObject(GetIndex(WalljumpL), path + "walljumpL.png", 0, 0);
	addObject(GetIndex(WalljumpR), path + "walljumpR.png", 0, 0);
	addObject(GetIndex(Water), path + "water1.png", 0, 0);
	addObject(GetIndex(Water2), path + "water2.png", 0, 0);
	addObject(GetIndex(Water3), path + "water3.png", 0, 0);

	addObject(GetIndex(Warp), path + "warp.png", 0, 0);
	addObject(GetIndex(PlayerStart), path + "playerstart.png", 0, 0);
	addObject(GetIndex(JumpRefresher), path + "jumprefresher.png", 15, 15);

	addObject(GetIndex(Save), path + "save.png", 0, 0, 2, 1);

	addObject(GetIndex(Bg), path + "bg.png", 0, 0, 1, 1, 0, bgType == BgType::Tile);
}

SkinObject::SkinObject(string filename, int xo, int yo, int xnum, int ynum, float speed, bool tile)
{
	auto tex = make_shared<sf::Texture>();
	tex->loadFromFile(filename);
	tex->setRepeated(tile);

	auto spr = make_shared<Sprite>(xo, yo);
	spr->addSheet(tex, xnum, ynum, false);

	texture = tex;
	sprite = spr;
	this->speed = speed;
}
void SkinManager::apply(shared_ptr<SkinPackage> package)
{
	curSkin = std::move(package);

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
