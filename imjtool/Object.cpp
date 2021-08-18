#include "Object.h"

#include "Game.h"

Object::Object()
{
}


void Object::setSprite(string name, bool setMask)
{
	sprite = Game::get().resourceManager.sprites[name];
	if (setMask)
	{
		maskSprite = sprite;
	}
}

void Object::setMask(string name)
{
	maskSprite = Game::get().resourceManager.sprites[name];
}

void Object::updateSprite()
{
	imageIndex += imageSpeed;
}

void Object::drawSelf()
{
	if (sprite != nullptr)
		sprite->draw(imageIndex, x, y, xorigin, yorigin, xscale, yscale, rotation, color);
}

void Object::drawMask()
{
	if (maskSprite != nullptr)
		maskSprite->draw(imageIndex, x, y, maskXorigin, maskYorigin, xscale, yscale, rotation, color);
}

void Object::setOrigin(float x, float y, bool setMask)
{
	xorigin = x;
	yorigin = y;
	if (setMask)
	{
		maskXorigin = x;
		maskYorigin = y;
	}
}

void Object::setMaskOrigin(float x, float y)
{
	maskXorigin = x;
	maskYorigin = y;
}

shared_ptr<Object> Object::placeMeeting(float x, float y, int index)
{
	for (auto i : Game::get().objectManager.objects)
	{
		if (i.get() == this)
		{
			continue;
		}
		if (i->index == index)
		{
			// check collision
			auto item1 = maskSprite->items[static_cast<int>(imageIndex) % maskSprite->items.size()];
			auto item2 = i->maskSprite->items[static_cast<int>(i->imageIndex) % i->maskSprite->items.size()];
			auto spr1 = item1->sprite;
			auto spr2 = item2->sprite;
			int x1 = round(x);
			int y1 = round(y);
			int x2 = round(i->x);
			int y2 = round(i->y);

			if (xscale == 1 && yscale == 1 && rotation == 0 && i->xscale == 1 && i->yscale == 1 && i->rotation == 0)
			{
				// simple mode
				spr1->setPosition(x1, y1);
				spr1->setRotation(rotation);
				spr1->setOrigin(maskXorigin, maskYorigin);
				spr1->setScale(xscale, yscale);
				auto rect1 = spr1->getGlobalBounds();
				
				spr2->setPosition(x2, y2);
				spr2->setRotation(i->rotation);
				spr2->setOrigin(i->maskXorigin, i->maskYorigin);
				spr2->setScale(i->xscale, i->yscale);
				auto rect2 = spr2->getGlobalBounds();

				int left = max(rect1.left, rect2.left);
				int top = max(rect1.top, rect2.top);
				int right = min(rect1.left + rect1.width, rect2.left + rect2.width);
				int bottom = min(rect1.top + rect1.height, rect2.top + rect2.height);

				if (left >= right || top >= bottom)
				{
					continue;
				}

				for (auto cy = top; cy < bottom; cy++)
				{
					for (auto cx = left; cx < right; cx++)
					{
						int c1x = cx - x1 + maskXorigin;
						int c1y = cy - y1 + maskYorigin;
						auto p1 = item1->data[c1x + c1y * item1->w];

						int c2x = cx - x2 + i->maskXorigin;
						int c2y = cy - y2 + i->maskYorigin;
						auto p2 = item2->data[c2x + c2y * item2->w];

						if (p1 && p2)
							return i;
					}
				}
			}
			else
			{
				// transform mode
				spr1->setPosition(x1, y1);
				spr1->setRotation(rotation);
				spr1->setOrigin(maskXorigin, maskYorigin);
				spr1->setScale(xscale, yscale);
				auto rect1 = spr1->getGlobalBounds();
				auto trans1 = spr1->getInverseTransform();

				spr2->setPosition(x2, y2);
				spr2->setRotation(i->rotation);
				spr2->setOrigin(i->maskXorigin, i->maskYorigin);
				spr2->setScale(i->xscale, i->yscale);
				auto rect2 = spr2->getGlobalBounds();
				auto trans2 = spr2->getInverseTransform();

				int left = max(rect1.left, rect2.left);
				int top = max(rect1.top, rect2.top);
				int right = min(rect1.left + rect1.width, rect2.left + rect2.width);
				int bottom = min(rect1.top + rect1.height, rect2.top + rect2.height);

				if (left >= right || top >= bottom)
				{
					continue;
				}

				for (auto cy = top; cy < bottom; cy++)
				{
					for (auto cx = left; cx < right; cx++)
					{
						sf::Vector2f p(cx, cy);

						auto c1 = trans1.transformPoint(p);
						auto p1 = c1.x >= 0 && c1.x < item1->w&& c1.y >= 0 && c1.y < item1->h&& item1->data[c1.x +
							c1.y * item1->w];

						auto c2 = trans2.transformPoint(p);
						auto p2 = c2.x >= 0 && c2.x < item2->w&& c2.y >= 0 && c2.y < item2->h&& item2->data[c2.x +
							c2.y * item2->w];

						if (p1 && p2)
							return i;
					}
				}
			}
		}
	}
	return nullptr;
}
