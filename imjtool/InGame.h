#pragma once
#include "Object.h"

class Apple :
    public Object
{
public:
    Apple();

    void update() override;
};

class Block :
    public Object
{
public:
    Block();

    void update() override;
};

class MiniBlock :
    public Object
{
public:
    MiniBlock();

    void update() override;
};

class JumpRefresher :
    public Object
{
public:
    JumpRefresher();

    void update() override;
};

class KillerBlock :
    public Object
{
public:
    KillerBlock();

    void update() override;
};

class MiniSpikeDown :
    public Object
{
public:
    MiniSpikeDown();

    void update() override;
};

class MiniSpikeLeft :
    public Object
{
public:
    MiniSpikeLeft();

    void update() override;
};

class MiniSpikeRight :
    public Object
{
public:
    MiniSpikeRight();

    void update() override;
};

class MiniSpikeUp :
    public Object
{
public:
    MiniSpikeUp();

    void update() override;
};

class Platform :
    public Object
{
public:
    Platform();

    void update() override;
};

class Player : public Object
{
public:
    float jump = 8.5;
    float jump2 = 7;
    float maxHspeed = 3;
    float maxVspeed = 9;
    bool onPlatform = false;
    int grav = 1;
    int face = 1;
    bool djump = true;

    Player();
    void update() override;
};

class PlayerStart :
    public Object
{
public:
    PlayerStart();

    void update() override;
};

class Save :
    public Object
{
public:
    Save();

    void update() override;
};

class SpikeDown :
    public Object
{
public:
    SpikeDown();

    void update() override;
};

class SpikeLeft :
    public Object
{
public:
    SpikeLeft();

    void update() override;
};

class SpikeRight :
    public Object
{
public:
    SpikeRight();

    void update() override;
};

class SpikeUp :
    public Object
{
public:
    SpikeUp();

    void update() override;
};

class WalljumpL :
    public Object
{
public:
    WalljumpL();

    void update() override;
};

class WalljumpR :
    public Object
{
public:
    WalljumpR();

    void update() override;
};

class Warp :
    public Object
{
public:
    Warp();

    void update() override;
};
class Water :
    public Object
{
public:
    Water();

    void update() override;
};

class World : public Object
{
public:
    void update() override;
};