#pragma once
#include "Object.h"
class JumpRefresher :
    public Object
{
public:
    JumpRefresher();

    void update() override;
};
