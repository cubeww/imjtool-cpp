#pragma once
#include "Object.h"
class Water :
    public Object
{
public:
    Water();

    void update() override;
};

