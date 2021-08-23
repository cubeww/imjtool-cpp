#include "Sprite.h"

#include <iostream>

#include "Game.h"
#include "ResourceManager.h"

void Sprite::addSheet(shared_ptr<sf::Texture> tex, int xnum, int ynum, bool getData)
{
	auto size = tex->getSize();
	int w = size.x / xnum;
	int h = size.y / ynum;
	for (auto y = 0; y < ynum; y++)
	{
		for (auto x = 0; x < xnum; x++)
		{
			auto spr = make_shared<sf::Sprite>();
			spr->setTexture(*tex);
			spr->setTextureRect(sf::IntRect(x*w, y*h, w, h));
			auto item = make_shared<SpriteItem>(spr, w, h);

			if (getData)
			{
				item->getData();
			}

			items.push_back(item);
		}
	}
}

void SpriteItem::getData()
{
	// get data
	auto image = sprite->getTexture()->copyToImage();
	auto& rect = sprite->getTextureRect();
	auto data = vector<bool>(w * h);
	auto left = w - 1;
	auto top = h - 1;
	auto right = 0;
	auto bottom = 0;
	auto i = 0;
	auto xs = rect.left;
	auto ys = rect.top;
	for (auto yy = ys; yy < rect.top + rect.height; yy++)
	{
		for (auto xx = xs; xx < rect.left + rect.width; xx++)
		{
			if (image.getPixel(xx, yy).a != 0)
			{
				data[i] = true;
				left = min(left, xx - xs);
				right = max(right, xx - xs);
				top = min(top, yy - ys);
				bottom = max(bottom, yy - ys);
			}
			else data[i] = false;
			i++;
		}
	}

	this->data = data;
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
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

SpriteItem::SpriteItem(shared_ptr<sf::Sprite> sprite, int w, int h)
{
	this->sprite = sprite;
	this->w = w;
	this->h = h;
}
