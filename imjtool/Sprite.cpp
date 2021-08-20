#include "Sprite.h"

#include <iostream>

#include "Game.h"
#include "ResourceManager.h"

void Sprite::addSingle(string textureName, int x, int y, int w, int h)
{
	auto tex = ResMgr.textures[textureName];
	auto spr = make_shared<sf::Sprite>();
	spr->setTexture(*tex);
	spr->setTextureRect(sf::IntRect(x, y, w, h));
	auto image = tex->copyToImage();
	// get data
	auto data = vector<bool>(w * h);
	auto i = 0;
	for (auto yy = 0; yy < h; yy++)
	{
		for (auto xx = 0; xx < w; xx++)
		{
			data[i] = image.getPixel(xx, yy).a != 0;
			i++;
		}
	}

	items.push_back(make_shared<SpriteItem>(spr, data, w, h));
}

void Sprite::addSheet(string textureName, int xnum, int ynum)
{
	auto tex = ResMgr.textures[textureName];
	auto size = tex->getSize();
	auto w = size.x / xnum;
	auto h = size.y / ynum;
	auto image = tex->copyToImage();
	for (auto y = 0; y < ynum; y++)
	{
		for (auto x = 0; x < xnum; x++)
		{
			auto spr = make_shared<sf::Sprite>();
			spr->setTexture(*tex);
			spr->setTextureRect(sf::IntRect(x*w, y*h, w, h));

			// get data
			auto data = vector<bool>(w * h);
			auto i = 0;
			for (auto yy = h * y; yy < h * y + h; yy++)
			{
				for (auto xx = w * x; xx < w * x + w; xx++)
				{
					data[i] = image.getPixel(xx, yy).a != 0;
					i++;
				}
			}

			items.push_back(make_shared< SpriteItem>(spr, data, w, h));
		}
	}
}

void Sprite::draw(int index, float x, float y, float xorigin, float yorigin, float xscale, float yscale, float rotation,
                  sf::Color color)
{
	auto spr = items[index % items.size()]->sprite;
	spr->setPosition(x, y);
	spr->setScale(xscale, yscale);
	spr->setRotation(rotation);
	spr->setPosition(x, y);
	spr->setColor(color);
	spr->setOrigin(xorigin, yorigin);
	Gm.gameTexture->draw(*spr);
}

SpriteItem::SpriteItem(shared_ptr<sf::Sprite> sprite, vector<bool> data, int w, int h)
{
	this->sprite = sprite;
	this->data = data;
	this->w = w;
	this->h = h;
}
