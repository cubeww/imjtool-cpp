#pragma once

#include <memory>
#include <vector>

class Object;

using namespace std;

// object helper macros
#define GetIndex(name) (static_cast<int>(Index::name))

#define CreateInst(index, x, y) ObjMgr.create(index, x, y)

#define DestroyInst(ptr) ptr->needDestroy = true
#define DestroyByIndex(_index) for_each(ObjMgr.objects.begin(), ObjMgr.objects.end(), [](shared_ptr<Object>& o){if(o->index == _index){o->needDestroy=true;}})
#define DestroyByName(name) DestroyByIndex(GetIndex(name))
#define DestroyThis() this->needDestroy = true
#define DestroyAll() for_each(ObjMgr.objects.begin(), ObjMgr.objects.end(), [](shared_ptr<Object>& o){o->needDestroy=true;})

#define ALL -1

#define RoundToInt(x) (static_cast<int>(x + 0.5f))
#define FloorToInt(x) (static_cast<int>(x))

inline bool equalF(float x, float y) { return fabs(x - y) < 0.0001; }

class ObjectManager
{
public:
	shared_ptr<Object> create(int index, float x, float y);

	vector<shared_ptr<Object>> objects;

	void update();

	shared_ptr<Object> collisionPoint(float x, float y, int index);
	vector<shared_ptr<Object>> collisionPointList(float x, float y, int index);

	vector<shared_ptr<Object>> collisionLineList(float x1, float y1, float x2, float y2, int index);

	vector<shared_ptr<Object>> atPosition(float x, float y, int index);
	int getCount(int index);
};
