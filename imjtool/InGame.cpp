#include "InGame.h"

#include <iostream>
#include "random.hpp"

using Random = effolkronium::random_static;
#define PI 3.1415926535897932f

void Apple::create()
{
	depth = 0;
	imageSpeed = 1 / 15;
	setSprite("apple");
	addCollision("Killer");
}

void Apple::update()
{
	drawSelf();
}

void Block::create()
{
	depth = 1;
	setSprite("block");
	addCollision("Block");
}

void Block::update()
{
	drawSelf();
}

void MiniBlock::create()
{
	depth = 1;
	setSprite("mini_block");
	addCollision("Block");
}

void MiniBlock::update()
{
	drawSelf();
}

void JumpRefresher::create()
{
	depth = 0;
	setSprite("jump_refresher");
	addCollision("JumpRefresher");
}

void JumpRefresher::update()
{
	drawSelf();
}

void KillerBlock::create()
{
	depth = 0;
	setSprite("killer_block");
	addCollision("Killer");
}

void KillerBlock::update()
{
	drawSelf();
}

void MiniSpikeDown::create()
{
	depth = 0;
	setSprite("mini_spike_down");
	addCollision("Killer");
}

void MiniSpikeDown::update()
{
	drawSelf();
}

void MiniSpikeLeft::create()
{
	depth = 0;
	setSprite("mini_spike_left");
	addCollision("Killer");
}

void MiniSpikeLeft::update()
{
	drawSelf();
}

void MiniSpikeRight::create()
{
	depth = 0;
	setSprite("mini_spike_right");
	addCollision("Killer");
}

void MiniSpikeRight::update()
{
	drawSelf();
}

void MiniSpikeUp::create()
{
	depth = 0;
	setSprite("mini_spike_up");
	addCollision("Killer");
}

void MiniSpikeUp::update()
{
	drawSelf();
}

void Platform::create()
{
	depth = 10;
	setSprite("platform");
	addCollision("Platform");
}

void Platform::update()
{
	drawSelf();
}

#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))

void Player::create()
{
	depth = -10;
	imageSpeed = 0.2;
	gravity = 0.4 * PlayerMgr.grav;

	setSprite("player_idle");
	setMask("player_mask");
	setOrigin(17, 23, true);
	addCollision("Player");

	for (auto i : ObjMgr.objects)
	{
		if (i.get() == this)
		{
			PlayerMgr.player = static_pointer_cast<Player>(i);
			break;
		}
	}
}

void Player::update()
{
	xprevious = x;
	yprevious = y;

	auto L = InputMgr.isKeyHold(sf::Keyboard::Left);
	auto R = InputMgr.isKeyHold(sf::Keyboard::Right);

	auto h = 0;
	if (R) h = 1;
	else if (L) h = -1;

	if (h != 0)
	{
		PlayerMgr.face = h;
		setSprite("player_running", false);
		setOrigin(17, 23, false);
		imageSpeed = 0.5;
	}
	else
	{
		setSprite("player_idle", false);
		setOrigin(17, 23, false);
		imageSpeed = 0.2;
	}
	hspeed = maxHspeed * h;
	if (!onPlatform)
	{
		if (vspeed * PlayerMgr.grav < -0.05)
		{
			setSprite("player_jump", false);
			setOrigin(17, 23, false);
		}
		else if (vspeed * PlayerMgr.grav > 0.05)
		{
			setSprite("player_fall", false);
			setOrigin(17, 23, false);
		}
	}
	if (!placeMeeting(x, y + 4 * PlayerMgr.grav, "Platform"))
	{
		onPlatform = false;
	}

	if (abs(vspeed) > maxVspeed)
	{
		vspeed = sign(vspeed) * maxVspeed;
	}

	auto water = placeMeeting(x, y, "Water");
	auto water2 = placeMeeting(x, y, "Water2");
	auto water3 = placeMeeting(x, y, "Water3");

	if (water || water2 || water3)
	{
		vspeed = min(vspeed * PlayerMgr.grav, 2.0f) * PlayerMgr.grav;

		if (!water2)
		{
			djump = true;
		}
	}

	if (InputMgr.isKeyPress(sf::Keyboard::LShift))
	{
		if (placeMeeting(x, y + 1 * PlayerMgr.grav, "Block") || placeMeeting(x, y + 1 * PlayerMgr.grav, "Platform") || onPlatform ||
			water)
		{
			vspeed = -jump * PlayerMgr.grav;
			djump = true;
		}
		else if (djump || water2)
		{
			setSprite("player_jump", false);
			setOrigin(17, 23, false);
			vspeed = -jump2 * PlayerMgr.grav;
			if (!water3)
				djump = false;
			else djump = true;
		}
	}

	if (InputMgr.isKeyRelease(sf::Keyboard::LShift))
	{
		if (vspeed * PlayerMgr.grav < 0)
		{
			vspeed *= 0.45;
		}
	}

	// vine
	auto notOnBlock = !placeMeeting(x, y + 1 * PlayerMgr.grav, "Block");
	auto onVineL = placeMeeting(x - 1, y, "WalljumpL") && notOnBlock;
	auto onVineR = placeMeeting(x + 1, y, "WalljumpR") && notOnBlock;
	if (onVineL || onVineR)
	{
		if (onVineL)
		{
			PlayerMgr.face = 1;
		}
		else
		{
			PlayerMgr.face = -1;
		}

		vspeed = 2 * PlayerMgr.grav;

		setSprite("player_sliding", false);
		setOrigin(7, 10, false);
		imageSpeed = 0.5;

		if ((onVineL && InputMgr.isKeyPress(sf::Keyboard::Right)) || (onVineR && InputMgr.isKeyPress(sf::Keyboard::Left)))
		{
			if (InputMgr.isKeyHold(sf::Keyboard::LShift))
			{
				if (onVineR) hspeed = -15;
				else hspeed = 15;
				vspeed = -9 * PlayerMgr.grav;
				setSprite("player_jump", false);
				setOrigin(17, 23, false);
			}
			else
			{
				if (onVineR) hspeed = -3;
				else hspeed = 3;
				setSprite("player_fall", false);
				setOrigin(17, 23, false);
			}
		}
	}

	// movement
	vspeed += gravity;
	x += hspeed;
	y += vspeed;

	// block
	auto dir = 0;
	if (placeMeeting(x, y, "Block"))
	{
		x = xprevious;
		y = yprevious;

		if (placeMeeting(x + hspeed, y, "Block"))
		{
			dir = sign(hspeed);
			while (!placeMeeting(x + dir, y, "Block"))
			{
				x += dir;
			}
			hspeed = 0;
		}
		if (placeMeeting(x, y + vspeed, "Block"))
		{
			dir = sign(vspeed);
			while (!placeMeeting(x, y + dir, "Block"))
			{
				y += dir;
			}
			if (vspeed * PlayerMgr.grav > 0)
			{
				djump = true;
			}
			vspeed = 0;
		}
		if (placeMeeting(x + hspeed, y + vspeed, "Block"))
		{
			hspeed = 0;
		}

		x += hspeed;
		y += vspeed;
	}

	// platform
	auto pf = placeMeeting(x, y, "Platform");
	if (pf != nullptr)
	{
		if (PlayerMgr.grav == 1)
		{
			if (y - vspeed / 2 <= pf->y)
			{
				y = pf->y - 9;
				vspeed = 0;

				onPlatform = true;
				djump = true;
			}
		}
		else
		{
			if (y - vspeed / 2 >= pf->y + pf->sprite->items[0]->h - 1)
			{
				y = pf->y + pf->sprite->items[0]->h + 8;
				vspeed = 0;

				onPlatform = true;
				djump = true;
			}
		}
	}

	auto flipGrav = [&]()
	{
		PlayerMgr.grav *= -1;
		gravity = 0.4 * PlayerMgr.grav;
		djump = true;
		vspeed = 0;

		if (PlayerMgr.grav == 1)
		{
			setMask("player_mask");
			setMaskOrigin(17, 23);
		}
		else
		{
			setMask("player_mask_flip");
			setMaskOrigin(17,8);
		}
		y += 4 * PlayerMgr.grav;
	};

	// gravity arrow
	if (PlayerMgr.grav == 1 && placeMeeting(x,y,"GravityArrowUp"))
	{
		flipGrav();
	}

	if (PlayerMgr.grav == -1 && placeMeeting(x, y, "GravityArrowDown"))
	{
		flipGrav();
	}

	// killer
	if (placeMeeting(x, y, "Killer"))
	{
		for(auto i = 0; i < 200; i++)
		{
			Create(Blood, x, y);
		}

		DestroyByName(Player);
		PlayerMgr.player = nullptr;
		return;
	}

	updateSprite();
	sprite->draw(imageIndex, x, y, xorigin, yorigin, PlayerMgr.face, PlayerMgr.grav, rotation, color);
	//drawMask();
}

void PlayerStart::create()
{
	for (auto const& o : ObjMgr.objects)
	{
		if (o->index == index && o.get() != this)
			Destroy(o);
	}
	DestroyByName(Player);
	Create(Player, x + 17, y + 23);
	depth = 0;
	setSprite("player_start");
	PlayerMgr.save();
}

void PlayerStart::update()
{
	drawSelf();
}

void Save::create()
{
	depth = 0;
	setSprite("save");
	addCollision("Save");
}

void Save::update()
{
	drawSelf();
}

void SpikeDown::create()
{
	depth = 0;
	setSprite("spike_down");
	addCollision("Killer");
}

void SpikeDown::update()
{
	drawSelf();
}

void SpikeLeft::create()
{
	depth = 0;
	setSprite("spike_left");
	addCollision("Killer");
}

void SpikeLeft::update()
{
	drawSelf();
}

void SpikeRight::create()
{
	depth = 0;
	setSprite("spike_right");
	addCollision("Killer");
}

void SpikeRight::update()
{
	drawSelf();
}

void SpikeUp::create()
{
	depth = 0;
	setSprite("spike_up");
	addCollision("Killer");
}

void SpikeUp::update()
{
	drawSelf();
}

void WalljumpL::create()
{
	depth = -1;
	setSprite("walljump_l");
	addCollision("WalljumpL");
}

void WalljumpL::update()
{
	drawSelf();
}

void WalljumpR::create()
{
	depth = -1;
	setSprite("walljump_r");
	addCollision("WalljumpR");
}

void WalljumpR::update()
{
	drawSelf();
}

void Warp::create()
{
	depth = 0;
	setSprite("warp");
	addCollision("Warp");
}

void Warp::update()
{
	drawSelf();
}

void Water::create()
{
	depth = -50;
	setSprite("water");
	addCollision("Water");
}

void Water::update()
{
	drawSelf();
}

void Water2::create()
{
	depth = -50;
	setSprite("water2");
	addCollision("Water2");
}

void Water2::update()
{
	drawSelf();
}


void Water3::create()
{
	depth = -50;
	setSprite("water3");
	addCollision("Water3");
}

void Water3::update()
{
	drawSelf();
}


void GravityArrowUp::create()
{
	depth = 0;
	setSprite("gravity_up");
	addCollision("GravityArrowUp");
}

void GravityArrowUp::update()
{
	drawSelf();
}


void GravityArrowDown::create()
{
	depth = 0;
	setSprite("gravity_down");
	addCollision("GravityArrowDown");
}

void GravityArrowDown::update()
{
	drawSelf();
}

void Blood::create()
{
	depth = -5;

	imageIndex = Random::get(0, 2);
	imageSpeed = 0;
	gravity = (0.1f + Random::get(0.0f, 0.2f)) * PlayerMgr.grav;
	auto direction = Random::get(0.0f, PI * 2);

	auto speed = Random::get(0.0f, 6.0f);
	hspeed = speed * cos(direction);
	vspeed = speed * sin(direction);

	xscale = 1.5;
	yscale = xscale;
	setSprite("blood");
	addCollision("Blood");
}

void Blood::update()
{
	xprevious = x;
	yprevious = y;

	vspeed += gravity;

	x += hspeed;
	y += vspeed;

	if (placeMeeting(x, y, "Block"))
	{
		x = xprevious;
		y = yprevious;

		while (!placeMeeting(x + sign(hspeed), y + sign(vspeed), "Block"))
		{
			x += sign(hspeed);
			y += sign(vspeed);
		}

		hspeed = 0;
		vspeed = 0;
		gravity = 0;
	}

	if (y >= 640)
	{
		DestroyThis();
		return;
	}

	drawSelf();
}