#pragma once
#include "Object.h"
class Block :
    public Object
{
public:
    Block();

    void update() override;
};

