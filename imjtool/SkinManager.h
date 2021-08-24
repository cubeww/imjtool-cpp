#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Sprite;

using namespace std;

class SkinObject
{
public:
	bool valid = false;
	shared_ptr<sf::Texture> texture;
	shared_ptr<Sprite> sprite;
	float speed = NAN;

	SkinObject(string filename, int xnum = 1, int ynum = 1, float speed = 0);
	SkinObject(shared_ptr<Sprite> sprite, float speed = 0);
};

enum class BgType
{
	Tile,
	Stretch,
};

class SkinPackage
{
public:
	shared_ptr<SkinObject> spikeUp;
	shared_ptr<SkinObject> spikeDown;
	shared_ptr<SkinObject> spikeLeft;
	shared_ptr<SkinObject> spikeRight;

	shared_ptr<SkinObject> miniSpikeUp;
	shared_ptr<SkinObject> miniSpikeDown;
	shared_ptr<SkinObject> miniSpikeLeft;
	shared_ptr<SkinObject> miniSpikeRight;

	shared_ptr<SkinObject> apple;
	shared_ptr<SkinObject> killerBlock;

	shared_ptr<SkinObject> block;
	shared_ptr<SkinObject> miniBlock;
	shared_ptr<SkinObject> bulletBlocker;
	shared_ptr<SkinObject> platform;

	shared_ptr<SkinObject> walljumpL;
	shared_ptr<SkinObject> walljumpR;
	shared_ptr<SkinObject> water;
	shared_ptr<SkinObject> water2;
	shared_ptr<SkinObject> water3;

	shared_ptr<SkinObject> warp;
	shared_ptr<SkinObject> playerStart;
	shared_ptr<SkinObject> jumpRefresher;

	shared_ptr<SkinObject> save;

	BgType bgType;
	float hspeed;
	float vspeed;

	SkinPackage();
	~SkinPackage() { cout << "free skin pkg" << endl; };
	SkinPackage(string name);
};

class SkinManager
{
public:
	vector<string> skinNames;
	shared_ptr<SkinPackage> curSkin;
	shared_ptr<SkinPackage> previewSkin;
	shared_ptr<SkinPackage> defaultSkin;

	void apply(shared_ptr<SkinPackage> package);

	void loadConfig();
	void loadDefault();
};

