#pragma once
#include "Object.h"
class KillerBlock :
    public Object
{
public:
    KillerBlock();

    void update() override;
};
