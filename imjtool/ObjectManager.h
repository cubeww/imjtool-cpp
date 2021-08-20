#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <functional>

class Object;

using namespace std;

// object helper macros
#define BEGIN_REGISTER int temp = 0;
#define REGISTER(name) indexMap[#name] = temp; temp += 1; createMap[indexMap[#name]] = [&](float x, float y){ auto obj = make_shared<name>(); obj->index = indexMap[#name]; obj->x = x; obj->y = y; objects.push_back(obj); obj->create(); return obj; };

#define GetIndex(name) ObjMgr.indexMap[#name]

#define Create(name, x, y) CreateByIndex(GetIndex(name), x, y)
#define CreateByIndex(index, x, y) ObjMgr.createMap[index](x, y)

#define Destroy(ptr) ptr->needDestroy = true
#define DestroyByIndex(_index) for_each(ObjMgr.objects.begin(), ObjMgr.objects.end(), [](shared_ptr<Object>& o){if(o->index == _index){o->needDestroy=true;}})
#define DestroyByName(name) DestroyByIndex(GetIndex(name))
#define DestroyThis() this->needDestroy = true
#define DestroyAll() for_each(ObjMgr.objects.begin(), ObjMgr.objects.end(), [](shared_ptr<Object>& o){o->needDestroy=true;})

#define ALL -1

class ObjectManager
{
public:
	ObjectManager();

	vector<shared_ptr<Object>> objects;
	map<string, int> indexMap;
	map<int, function<shared_ptr<Object>(float, float)>> createMap;

	void update();

	shared_ptr<Object> collisionPoint(float x, float y, int index);
	vector<shared_ptr<Object>> collisionPointList(float x, float y, int index);

	shared_ptr<Object> collisionLine(float x1, float y1, float x2, float y2, int index);
	vector<shared_ptr<Object>> collisionLineList(float x1, float y1, float x2, float y2, int index);

	vector<shared_ptr<Object>> atPosition(float x, float y, int index);
};
