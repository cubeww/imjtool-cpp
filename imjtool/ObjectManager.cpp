#include "ObjectManager.h"

#include "InGame.h"

#define floateq(x, y) (fabs(x - y) < 0.0001)

ObjectManager::ObjectManager()
{
	BEGIN_REGISTER
	REGISTER(Apple)
	REGISTER(Block)
	REGISTER(MiniBlock)
	REGISTER(JumpRefresher)
	REGISTER(KillerBlock)
	REGISTER(Platform)
	REGISTER(Player)
	REGISTER(PlayerStart)
	REGISTER(Save)
	REGISTER(Warp)
	REGISTER(SpikeDown)
	REGISTER(SpikeLeft)
	REGISTER(SpikeRight)
	REGISTER(SpikeUp)
	REGISTER(MiniSpikeDown)
	REGISTER(MiniSpikeLeft)
	REGISTER(MiniSpikeRight)
	REGISTER(MiniSpikeUp)
	REGISTER(WalljumpL)
	REGISTER(WalljumpR)
	REGISTER(Water)
	REGISTER(Water2)
	REGISTER(Water3)
	REGISTER(GravityArrowUp)
	REGISTER(GravityArrowDown)
}

void ObjectManager::update()
{
	// sort depth
	sort(objects.begin(), objects.end(), [](const shared_ptr<Object>& obj1, const shared_ptr<Object>& obj2)
	{
		return (obj1->depth > obj2->depth);
	});

	// update instances
	for (auto i : objects)
	{
		i->update();
	}
}

shared_ptr<Object> ObjectManager::collisionPoint(float x, float y, int index)
{
	for (auto i : ObjMgr.objects)
	{
		if (index == ALL || i->index == index)
		{
			// check collision
			auto item = i->maskSprite->items[static_cast<int>(i->imageIndex) % i->maskSprite->items.size()];
			auto spr = item->sprite;
			int x1 = round(x);
			int y1 = round(y);

			spr->setPosition(i->x, i->y);
			spr->setRotation(i->rotation);
			spr->setOrigin(i->maskXorigin, i->maskYorigin);
			spr->setScale(i->xscale, i->yscale);
			auto& trans = spr->getInverseTransform();

			auto c1 = trans.transformPoint(sf::Vector2f(x1, y1));
			if (c1.x >= 0 && c1.x < item->w - 1 && c1.y >= 0 && c1.y < item->h - 1 && item->data[c1.x +
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
	for (auto i : ObjMgr.objects)
	{
		if (index == ALL || i->index == index)
		{
			// check collision
			auto item = i->maskSprite->items[static_cast<int>(i->imageIndex) % i->maskSprite->items.size()];
			auto spr = item->sprite;
			int x1 = round(x);
			int y1 = round(y);

			spr->setPosition(i->x, i->y);
			spr->setRotation(i->rotation);
			spr->setOrigin(i->maskXorigin, i->maskYorigin);
			spr->setScale(i->xscale, i->yscale);
			auto& trans = spr->getInverseTransform();

			auto c1 = trans.transformPoint(sf::Vector2f(x1, y1));
			if (c1.x >= 0 && c1.x < item->w - 1 && c1.y >= 0 && c1.y < item->h - 1 && item->data[c1.x +
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
	for (auto i : ObjMgr.objects)
	{
		if (index == ALL || i->index == index)
		{
			auto d = sqrtf(powf(x1 - x2, 2) + powf(y1 - y2, 2));
			auto dx = (x2 - x1) / d;
			auto dy = (y2 - y1) / d;

			for (auto j = 0; j < d; j++)
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
	auto d = sqrtf(powf(x1 - x2, 2) + powf(y1 - y2, 2));
	auto dx = (x2 - x1) / d;
	auto dy = (y2 - y1) / d;

	auto xs = round(x1);
	auto ys = round(y1);

	for (auto i : ObjMgr.objects)
	{
		if (index == ALL || i->index == index)
		{
			// check collision
			auto item = i->maskSprite->items[static_cast<int>(i->imageIndex) % i->maskSprite->items.size()];
			auto spr = item->sprite;

			spr->setPosition(i->x, i->y);
			spr->setRotation(i->rotation);
			spr->setOrigin(i->maskXorigin, i->maskYorigin);
			spr->setScale(i->xscale, i->yscale);
			auto& trans = spr->getInverseTransform();

			auto xx = xs;
			auto yy = ys;
			for (float j = 0; j < d; j += 1)
			{
				auto c1 = trans.transformPoint(sf::Vector2f(xx, yy));
				if (c1.x >= 0 && c1.x < item->w - 1 && c1.y >= 0 && c1.y < item->h - 1 && item->data[c1.x +
					c1.y * item->w])
				{
					result.push_back(i);
				}

				xx += dx;
				yy += dy;
			}
		}
	}
	return result;
}

vector<shared_ptr<Object>> ObjectManager::atPosition(float x, float y, int index)
{
	vector<shared_ptr<Object>> result;
	for (auto i : ObjMgr.objects)
	{
		if (index == ALL || i->index == index)
		{
			if (floateq(x, i->x) && floateq(y, i->y))
			{
				result.push_back(i);
			}
		}
	}
	return result;
}
