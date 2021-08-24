#pragma once
#include "Object.h"

#define PI 3.1415926535897932f

enum class Index
{
    // collision
    Player,
    Block,
    Platform,
    Killer,
    Save,
    Water,
    Water2,
    Water3,
    WalljumpL,
    WalljumpR,
    GravityArrowUp,
    GravityArrowDown,
    JumpRefresher,
    Warp,
    Blood,
    PlayerBullet,
    BulletBlocker,

    // no collision
    SpikeUp,
    SpikeDown,
    SpikeLeft,
    SpikeRight,
    MiniSpikeUp,
    MiniSpikeDown,
    MiniSpikeLeft,
    MiniSpikeRight,
    Apple,
    KillerBlock,
    PlayerStart,
    MiniBlock,
    Bg,
};

string spriteOf(int index);
bool inPalette(int index);
bool isSkinable(int index);

class Apple :
    public Object
{
public:
    void create() override;
    void update() override;
};

class Block :
    public Object
{
public:
    void create() override;
    void update() override;
};

class MiniBlock :
    public Object
{
public:
    void create() override;
    void update() override;
};

class JumpRefresher :
    public Object
{
public:
    void create() override;
    void update() override;
};

class KillerBlock :
    public Object
{
public:
    void create() override;
    void update() override;
};

class MiniSpikeDown :
    public Object
{
public:
    void create() override;
    void update() override;
};

class MiniSpikeLeft :
    public Object
{
public:
    void create() override;
    void update() override;
};

class MiniSpikeRight :
    public Object
{
public:
    void create() override;
    void update() override;
};

class MiniSpikeUp :
    public Object
{
public:
    void create() override;
    void update() override;
};

class Platform :
    public Object
{
public:
    void create() override;
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
    bool djump = true;

    void create() override;
    void update() override;
};

class PlayerStart :
    public Object
{
public:
    void create() override;
    void update() override;
};

class Save :
    public Object
{
public:
    int timer = 0;
    int timer2 = 0;
    bool canSave = false;
    
    void save();
    void create() override;
    void update() override;
};

class SpikeDown :
    public Object
{
public:
    void create() override;
    void update() override;
};

class SpikeLeft :
    public Object
{
public:
    void create() override;
    void update() override;
};

class SpikeRight :
    public Object
{
public:
    void create() override;
    void update() override;
};

class SpikeUp :
    public Object
{
public:
    void create() override;
    void update() override;
};

class WalljumpL :
    public Object
{
public:
    void create() override;
    void update() override;
};

class WalljumpR :
    public Object
{
public:
    void create() override;
    void update() override;
};

class Warp :
    public Object
{
public:
    void create() override;
    void update() override;
};

class Water :
    public Object
{
public:
    void create() override;
    void update() override;
};

class Water2 :
    public Object
{
public:
    void create() override;
    void update() override;
};

class Water3 :
    public Object
{
public:
    void create() override;
    void update() override;
};

class GravityArrowUp :
    public Object
{
public:
    void create() override;
    void update() override;
};

class GravityArrowDown :
    public Object
{
public:
    void create() override;
    void update() override;
};

class Blood :
    public Object
{
public:
    void create() override;
    void update() override;
};

class PlayerBullet :
    public Object
{
    int timer = 0;
public:
    void create() override;
    void update() override;
};

class BulletBlocker :
    public Object
{
public:
    void create() override;
    void update() override;
};

class Bg :
    public Object
{
public:
    // 0 1 2
    // 3 4 5
    // 6 7 8
    // 9 - tile rect
    sf::RectangleShape rects[10];

    void create() override;
    void update() override;
};