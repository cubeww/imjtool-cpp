#pragma once
#include <iostream>
#include <map>
#include "SFML/Graphics.hpp"

class Sprite;

using namespace std;

class SkinObject
{
public:
	shared_ptr<sf::Texture> texture;
	shared_ptr<Sprite> sprite;
	float speed = NAN;

	SkinObject(string filename, int xo, int yo, int xnum = 1, int ynum = 1, float speed = NAN, bool tile = true);
};

enum class BgType
{
	Tile,
	Stretch,
};

class SkinPackage
{
public:
	string skinName;
	map<string, shared_ptr<SkinObject>> objects;

	BgType bgType;
	float hspeed;
	float vspeed;

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

	shared_ptr<SkinObject> getCurrent(string name);
	shared_ptr<Sprite> getCurrentSprite(string name);

	shared_ptr<SkinObject> getPreview(string name);
};

