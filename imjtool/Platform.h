#pragma once
#include "Object.h"
class Platform :
    public Object
{
public:
    Platform();

    void update() override;
};

