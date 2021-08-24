#include "ObjectManager.h"

#include "InGame.h"
#include "Object.h"

#define REGISTER(name) \
case Index::name: \
	obj = make_shared<name>(); \
	objects.push_back(obj); \
	obj->index = index; \
	obj->x = x; \
	obj->y = y; \
	obj->weakPtr = weak_ptr<Object>(obj); \
	obj->create(); \
	break;

shared_ptr<Object> ObjectManager::create(int index, float x, float y)
{
	shared_ptr<Object> obj;
	switch (static_cast<Index>(index))
	{
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
			REGISTER(Blood)
			REGISTER(PlayerBullet)
			REGISTER(BulletBlocker)
			REGISTER(Bg)

	default:
		break;
	}
	return obj;
}


void ObjectManager::update()
{
	// sort depth
	sort(objects.begin(), objects.end(), [](const shared_ptr<Object>& obj1, const shared_ptr<Object>& obj2)
		{
			return (obj1->depth > obj2->depth);
		});

	// update instances
	for (auto i = 0; i < static_cast<int>(objects.size());)
	{
		auto& obj = objects[i];
		if (obj->needDestroy)
		{
			objects.erase(objects.begin() + i);
		}
		else
		{
			obj->update();
			++i;
		}
	}
}

shared_ptr<Object> ObjectManager::collisionPoint(float x, float y, int index)
{
	auto x1 = RoundToInt(x);
	auto y1 = RoundToInt(y);
	for (const auto& i : ObjMgr.objects)
	{
		if (i->maskSprite != nullptr && (index == ALL || i->index == index))
		{
			// check collision
			auto& item = i->maskSprite->items[FloorToInt(i->imageIndex) % i->maskSprite->items.size()];

			int xx, yy;

			if (equalF(i->rotation, 0))
			{
				xx = FloorToInt((x1 - i->x) / i->xscale + i->xorigin);
				yy = FloorToInt((y1 - i->y) / i->yscale + i->yorigin);
			}
			else
			{
				auto ss = sin(-i->rotation * PI / 180);
				auto cc = cos(-i->rotation * PI / 180);
				xx = FloorToInt((cc * (x1 - i->x) + ss * (y1 - i->y)) / i->xscale + i->xorigin);
				yy = FloorToInt((cc * (y1 - i->y) - ss * (x1 - i->x)) / i->yscale + i->yorigin);
			}

			if (xx < 0 || xx >= item->w) continue;
			if (yy < 0 || yy >= item->h) continue;
			if (!item->data[xx + (yy * item->w)]) continue;
			return i;
		}
	}
	return nullptr;
}

vector<shared_ptr<Object>> ObjectManager::collisionPointList(float x, float y, int index)
{
	vector<shared_ptr<Object>> result;
	auto x1 = RoundToInt(x);
	auto y1 = RoundToInt(y);

	for (const auto& i : ObjMgr.objects)
	{
		if (i->maskSprite != nullptr && (index == ALL || i->index == index))
		{
			// check collision
			auto& item = i->maskSprite->items[FloorToInt(i->imageIndex) % i->maskSprite->items.size()];
			int xx, yy;

			if (equalF(i->rotation, 0))
			{
				xx = FloorToInt((x1 - i->x) / i->xscale + i->xorigin);
				yy = FloorToInt((y1 - i->y) / i->yscale + i->yorigin);
			}
			else
			{
				auto ss = sin(-i->rotation * PI / 180);
				auto cc = cos(-i->rotation * PI / 180);
				xx = FloorToInt((cc * (x1 - i->x) + ss * (y1 - i->y)) / i->xscale + i->xorigin);
				yy = FloorToInt((cc * (y1 - i->y) - ss * (x1 - i->x)) / i->yscale + i->yorigin);
			}

			if (xx < 0 || xx >= item->w) continue;
			if (yy < 0 || yy >= item->h) continue;
			if (!item->data[xx + (yy * item->w)]) continue;
			result.push_back(i);
		}
	}
	return result;
}

vector<shared_ptr<Object>> ObjectManager::collisionLineList(float x1, float y1, float x2, float y2, int index)
{
	vector<shared_ptr<Object>> result;
	auto d = sqrtf(powf(x1 - x2, 2) + powf(y1 - y2, 2));
	auto dx = (x2 - x1) / d;
	auto dy = (y2 - y1) / d;

	for (const auto& i : ObjMgr.objects)
	{
		if (i->maskSprite != nullptr && (index == ALL || i->index == index))
		{
			// check collision
			auto& item = i->maskSprite->items[static_cast<int>(i->imageIndex) % i->maskSprite->items.size()];

			x2 = x1;
			y2 = y1;

			for (float j = 0; j < d; j += 1)
			{
				int xx, yy;
				if (equalF(i->rotation, 0))
				{
					xx = FloorToInt((x2 - i->x) / i->xscale + i->xorigin);
					yy = FloorToInt((y2 - i->y) / i->yscale + i->yorigin);
				}
				else
				{
					auto ss = sin(-i->rotation * PI / 180);
					auto cc = cos(-i->rotation * PI / 180);
					xx = FloorToInt((cc * (x2 - i->x) + ss * (y2 - i->y)) / i->xscale + i->xorigin);
					yy = FloorToInt((cc * (y2 - i->y) - ss * (x2 - i->x)) / i->yscale + i->yorigin);
				}

				if ((xx < 0 || xx >= item->w) ||
					(yy < 0 || yy >= item->h) ||
					(!item->data[xx + (yy * item->w)]))
				{
					x2 += dx;
					y2 += dy;
					continue;
				}

				result.push_back(i);
				x2 += dx;
				y2 += dy;
			}
		}
	}
	return result;
}

vector<shared_ptr<Object>> ObjectManager::atPosition(float x, float y, int index)
{
	vector<shared_ptr<Object>> result;
	for (const auto& i : ObjMgr.objects)
	{
		if (index == ALL || i->index == index)
		{
			if (equalF(x, i->x) && equalF(y, i->y))
			{
				result.push_back(i);
			}
		}
	}
	return result;
}

int ObjectManager::getCount(int index)
{
	auto result = 0;
	for (auto const& i : objects)
	{
		if (i->index == index)
		{
			result++;
		}
	}
	return result;
}
