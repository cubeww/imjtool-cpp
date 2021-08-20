#include "ResourceManager.h"

void ResourceManager::createTexture(string name, string filename)
{
	auto tex = make_shared<sf::Texture>();
	tex->loadFromFile(filename);
	textures[name] = tex;
}

Sprite& ResourceManager::createSprite(string name)
{
	auto spr = make_shared<Sprite>();
	sprites[name] = spr;
	return *spr;
}
