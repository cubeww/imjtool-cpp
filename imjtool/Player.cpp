#include "Player.h"

#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))

Player::Player()
{
	imageSpeed = 0.2;
	gravity = 0.4 * grav;

	setSprite("player_idle");
	setMask("player_mask");
	setOrigin(17, 23, true);
}

void Player::update()
{
	xprevious = x;
	yprevious = y;

	auto L = IS_HOLD(sf::Keyboard::Left);
	auto R = IS_HOLD(sf::Keyboard::Right);

	auto h = 0;
	if (R) h = 1;
	else if (L) h = -1;

	if (h != 0)
	{
		face = h;
		setSprite("player_running", false);
		imageSpeed = 0.5;
	}
	else
	{
		setSprite("player_idle", false);
		imageSpeed = 0.2;
	}
	hspeed = maxHspeed * h;
	if (!onPlatform)
	{
		if (vspeed * grav < -0.05)
		{
			setSprite("player_jump", false);
		}
		else if (vspeed * grav > 0.05)
		{
			setSprite("player_fall", false);
		}
	}
	if (!placeMeeting(x, y + 4 * grav, GETID(Platform)))
	{
		onPlatform = false;
	}

	if (abs(vspeed) > maxVspeed)
	{
		vspeed = sign(vspeed) * maxVspeed;
	}

	if (IS_PRESS(sf::Keyboard::LShift))
	{
		if (placeMeeting(x, y + 1 * grav, GETID(Block)))
		{
			vspeed = -jump * grav;
			djump = true;
		}
		else if (djump)
		{
			setSprite("player_jump", false);
			vspeed = -jump2 * grav;
			djump = false;
		}
	}

	if (IS_RELEASE(sf::Keyboard::LShift))
	{
		if (vspeed * grav < 0)
		{
			vspeed *= 0.45;
		}
	}
	vspeed += gravity;
	x += hspeed;
	y += vspeed;

	// block
	auto dir = 0;
	if (placeMeeting(x, y, GETID(Block)))
	{
		x = xprevious;
		y = yprevious;

		if (placeMeeting(x + hspeed, y, GETID(Block)))
		{
			dir = sign(hspeed);
			while (!placeMeeting(x + dir, y, GETID(Block)))
			{
				x += dir;
			}
			hspeed = 0;
		}
		if (placeMeeting(x, y + vspeed, GETID(Block)))
		{
			dir = sign(vspeed);
			while (!placeMeeting(x, y + dir, GETID(Block)))
			{
				y += dir;
			}
			if (vspeed * grav > 0)
			{
				djump = true;
			}
			vspeed = 0;
		}
		if (placeMeeting(x + hspeed, y + vspeed, GETID(Block)))
		{
			hspeed = 0;
		}

		x += hspeed;
		y += vspeed;
	}

	updateSprite();
	sprite->draw(imageIndex, x, y, xorigin, yorigin, face, grav, rotation, color);
	//drawMask();
}
