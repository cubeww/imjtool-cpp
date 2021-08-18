#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <functional>

class Object;

using namespace std;

#define BEGIN_REGISTER int temp = 0;
#define REGISTER(name) indexMap[#name] = temp; temp += 1; createMap[indexMap[#name]] = [&](float x, float y){ auto obj = make_shared<name>(); obj->x = x; obj->y = y; obj->index = indexMap[#name]; objects.push_back(obj); return obj; };
#define GETID(name) Game::get().objectManager.indexMap[#name]

#define CREATE(name, x, y) Game::get().objectManager.create(make_shared<name>(), x, y)->index = GETID(name)
#define CREATEI(index, x, y) Game::get().objectManager.createMap[index](x, y)

class ObjectManager
{
public:
	ObjectManager();

	vector<shared_ptr<Object>> objects;
	map<string, int> indexMap;
	map<int, function<shared_ptr<Object>(float, float)>> createMap;

	shared_ptr<Object> create(shared_ptr<Object> obj, float x = 0, float y = 0);

	void update();

	shared_ptr<Object> collisionPoint(float x, float y, int index);
	vector<shared_ptr<Object>> collisionPointList(float x, float y, int index);

	shared_ptr<Object> collisionLine(float x1, float y1, float x2, float y2, int index);
	vector<shared_ptr<Object>> collisionLineList(float x1, float y1, float x2, float y2, int index);

	vector<shared_ptr<Object>> atPosition(float x, float y, int index);
};
