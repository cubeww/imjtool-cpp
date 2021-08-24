#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class SpriteItem;

class Sprite
{
public:
	Sprite(int xo, int yo);

	vector<shared_ptr<SpriteItem>> items;
	int xOrigin = 0;
	int yOrigin = 0;

	void addSheet(shared_ptr<sf::Texture> tex, int xnum = 1, int ynum = 1, bool getData = true);

	void draw(int index, float x, float y, float xorigin, float yorigin, float xscale, float yscale, float rotation, sf::Color color);
};

class SpriteItem
{
public:
	shared_ptr<sf::Sprite> sprite;
	int w;
	int h;

	vector<bool> data;
	int left;
	int right;
	int top;
	int bottom;

	SpriteItem(shared_ptr<sf::Sprite> sprite, int w, int h);
	void getData();
};