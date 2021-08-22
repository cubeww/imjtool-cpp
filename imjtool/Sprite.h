#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class SpriteItem;

class Sprite
{
public:
	vector<shared_ptr<SpriteItem>> items;

	void addSingle(string textureName, int x, int y, int w, int h);
	void addSheet(string textureName, int xnum = 1, int ynum = 1);

	void draw(int index, float x, float y, float xorigin, float yorigin, float xscale, float yscale, float rotation, sf::Color color);
};

class SpriteItem
{
public:
	shared_ptr<sf::Sprite> sprite;
	vector<bool> data;
	int w;
	int h;

	int left;
	int right;
	int top;
	int bottom;

	SpriteItem(shared_ptr<sf::Sprite> sprite, vector<bool> data, int w, int h, int left, int right, int top, int bottom);
};