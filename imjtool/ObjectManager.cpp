#include "ObjectManager.h"

#include "Block.h"
#include "Object.h"
#include "Platform.h"
#include "Player.h"
#include "SpikeDown.h"
#include "SpikeLeft.h"
#include "SpikeRight.h"
#include "SpikeUp.h"
#include "WalljumpL.h"
#include "WalljumpR.h"
#include "Water.h"
#include "World.h"

#define floateq(x, y) (fabs(x - y) < 0.0001)

ObjectManager::ObjectManager()
{
	BEGIN_REGISTER
	REGISTER(World)
	REGISTER(Block)
	REGISTER(Platform)
	REGISTER(Player)
	REGISTER(SpikeDown)
	REGISTER(SpikeLeft)
	REGISTER(SpikeRight)
	REGISTER(SpikeUp)
	REGISTER(WalljumpL)
	REGISTER(WalljumpR)
	REGISTER(Water)
}

shared_ptr<Object> ObjectManager::create(shared_ptr<Object> obj, float x, float y)
{
	objects.push_back(obj);
	obj->x = x;
	obj->y = y;
	return obj;
}

void ObjectManager::update()
{
	for (auto i : objects)
	{
		i->update();
	}
}

shared_ptr<Object> ObjectManager::collisionPoint(float x, float y, int index)
{
	for (auto i : Game::get().objectManager.objects)
	{
		if (i->index == index)
		{
			// check collision
			auto item = i->maskSprite->items[static_cast<int>(i->imageIndex) % i->maskSprite->items.size()];
			auto spr = item->sprite;
			int x1 = round(i->x);
			int y1 = round(i->y);

			spr->setPosition(x1, y1);
			spr->setRotation(i->rotation);
			spr->setOrigin(i->maskXorigin, i->maskYorigin);
			spr->setScale(i->xscale, i->yscale);
			auto trans = spr->getInverseTransform();

			auto c1 = trans.transformPoint(sf::Vector2f(x1, y1));
			if (c1.x >= 0 && c1.x < item->w && c1.y >= 0 && c1.y < item->h && item->data[c1.x +
				c1.y * item->w])
			{
				return i;
			}
		}
	}
	return nullptr;
}

vector<shared_ptr<Object>> ObjectManager::collisionPointList(float x, float y, int index)
{
	vector<shared_ptr<Object>> result;
	for (auto i : Game::get().objectManager.objects)
	{
		if (index == -1 || i->index == index)
		{
			// check collision
			auto item = i->maskSprite->items[static_cast<int>(i->imageIndex) % i->maskSprite->items.size()];
			auto spr = item->sprite;
			int x1 = round(i->x);
			int y1 = round(i->y);

			spr->setPosition(x1, y1);
			spr->setRotation(i->rotation);
			spr->setOrigin(i->maskXorigin, i->maskYorigin);
			spr->setScale(i->xscale, i->yscale);
			auto trans = spr->getInverseTransform();

			auto c1 = trans.transformPoint(sf::Vector2f(x1, y1));
			if (c1.x >= 0 && c1.x < item->w && c1.y >= 0 && c1.y < item->h && item->data[c1.x +
				c1.y * item->w])
			{
				result.push_back(i);
			}
		}
	}
	return result;
}

shared_ptr<Object> ObjectManager::collisionLine(float x1, float y1, float x2, float y2, int index)
{
	for (auto i : Game::get().objectManager.objects)
	{
		if (i->index == index)
		{
			auto d = sqrtf(powf(x1 - x2, 2) + powf(y1 - y2, 2));
			auto dx = (x2 - x1) / d;
			auto dy = (y2 - y1) / d;

			for(auto j = 0; j < d; j++)
			{
				auto col = collisionPoint(dx, dy, index);
				if (col != nullptr)
				{
					return col;
				}
			}
		}
	}
	return nullptr;
}

vector<shared_ptr<Object>> ObjectManager::collisionLineList(float x1, float y1, float x2, float y2, int index)
{
	vector<shared_ptr<Object>> result;
	for (auto i : Game::get().objectManager.objects)
	{
		if (i->index == index)
		{
			auto d = sqrtf(powf(x1 - x2, 2) + powf(y1 - y2, 2));
			auto dx = (x2 - x1) / d;
			auto dy = (y2 - y1) / d;

			for (auto j = 0; j < d; j++)
			{
				auto col = collisionPoint(dx, dy, index);
				if (col != nullptr)
				{
					result.push_back(col);
				}
			}
		}
	}
	return result;
}

vector<shared_ptr<Object>> ObjectManager::atPosition(float x, float y, int index)
{
	vector<shared_ptr<Object>> result;
	for (auto i : Game::get().objectManager.objects)
	{
		if (i->index == index)
		{
			if (floateq(x, i->x) && floateq(y, i->y))
			{
				result.push_back(i);
			}
		}
	}
	return result;
}