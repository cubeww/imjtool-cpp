#pragma once
#include "Object.h"
class Apple :
    public Object
{
public:
    Apple();

    void update() override;
};
