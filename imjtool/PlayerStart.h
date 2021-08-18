#pragma once
#include "Object.h"
class PlayerStart :
    public Object
{
public:
    PlayerStart();

    void update() override;
};
