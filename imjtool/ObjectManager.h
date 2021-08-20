#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <functional>

class Object;

using namespace std;

#define BEGIN_REGISTER int temp = 0;
#define REGISTER(name) indexMap[#name] = temp; temp += 1; createMap[indexMap[#name]] = [&](float x, float y){ auto obj = make_shared<name>(); obj->index = indexMap[#name]; obj->x = x; obj->y = y; objects.push_back(obj); obj->create(); return obj; };
#define GETID(name) ObjMgr.indexMap[#name]

#define CREATE(name, x, y) CREATEI(GETID(name), x, y)
#define CREATEI(index, x, y) ObjMgr.createMap[index](x, y)

#define DESTROY(ptr) ObjMgr.objects.erase(std::remove(ObjMgr.objects.begin(), ObjMgr.objects.end(), ptr), ObjMgr.objects.end());
#define DESTROYI(_index) ObjMgr.objects.erase(std::remove_if(ObjMgr.objects.begin(),ObjMgr.objects.end(),[](const shared_ptr<Object>& o){return o->index == _index;}),ObjMgr.objects.end())
#define DESTROYN(name) DESTROYI(GETID(name))
#define DESTROYALL() ObjMgr.objects.clear()

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
