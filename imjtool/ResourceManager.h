#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Sprite.h"

using namespace std;

class ResourceManager
{
public:
	map<string, shared_ptr<sf::Texture>> textures;
	map<string, shared_ptr<Sprite>> sprites;
	map<string, shared_ptr<sf::SoundBuffer>> soundBuffers;
	map<string, shared_ptr<sf::Sound>> sounds;

	void createTexture(string name, string filename);
	Sprite& createSprite(string name);
	void createSound(string name, string filename);
	
};
