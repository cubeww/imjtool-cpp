#pragma once

#include <SFML/Graphics.hpp>

#include "Sprite.h"

using namespace std;

class ResourceManager
{
public:
	map<string, shared_ptr<sf::Texture>> textures;
	map<string, shared_ptr<Sprite>> sprites;

	void createTexture(string name, string filename);
	Sprite& createSprite(string name);
	
};
