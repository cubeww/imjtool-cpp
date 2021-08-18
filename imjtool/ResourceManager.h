#pragma once

#include <SFML/Graphics.hpp>

#include "Sprite.h"

using namespace std;

class ResourceManager
{
public:
	map<string, shared_ptr<sf::Texture>> textures;
	map<string, shared_ptr<Sprite>> sprites;

	void createTexture(string name, string filename)
	{
		auto tex = make_shared<sf::Texture>();
		tex->loadFromFile(filename);
		textures[name] = tex;
	}

	Sprite& createSprite(string name)
	{
		auto spr = make_shared<Sprite>();
		sprites[name] = spr;
		return *spr;
	}
};
