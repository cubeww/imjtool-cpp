#include "InGame.h"

#include <iostream>
#include "random.hpp"

using Random = effolkronium::random_static;

bool inPalette(int index)
{
	switch (static_cast<Index>(index))
	{
	case Index::SpikeUp:
	case Index::SpikeDown:
	case Index::SpikeLeft:
	case Index::SpikeRight:
	case Index::MiniSpikeUp:
	case Index::MiniSpikeDown:
	case Index::MiniSpikeLeft:
	case Index::MiniSpikeRight:
	case Index::Block:
	case Index::MiniBlock:
	case Index::Apple:
	case Index::Save:
	case Index::Platform:
	case Index::KillerBlock:
	case Index::Water:
	case Index::Water2:
	case Index::Water3:
	case Index::WalljumpL:
	case Index::WalljumpR:
	case Index::PlayerStart:
	case Index::Warp:
	case Index::JumpRefresher:
	case Index::GravityArrowUp:
	case Index::GravityArrowDown:
		return true;
	default:
		return false;
	}
}

void Apple::create()
{
	depth = 0;
	imageSpeed = 1 / 15;
	setSprite("apple");
	addCollision(Index::Killer);
}

void Apple::update()
{
	drawSelf();
}

void Block::create()
{
	depth = 1;
	setSprite("block");
	addCollision(Index::Block);
}

void Block::update()
{
	drawSelf();
}

void MiniBlock::create()
{
	depth = 1;
	setSprite("mini_block");
	addCollision(Index::Block);
}

void MiniBlock::update()
{
	drawSelf();
}

void JumpRefresher::create()
{
	depth = 0;
	setSprite("jump_refresher");
	addCollision(Index::JumpRefresher);
}

void JumpRefresher::update()
{
	drawSelf();
}

void KillerBlock::create()
{
	depth = 0;
	setSprite("killer_block");
	addCollision(Index::Killer);
}

void KillerBlock::update()
{
	drawSelf();
}

void MiniSpikeDown::create()
{
	depth = 0;
	setSprite("mini_spike_down");
	addCollision(Index::Killer);
}

void MiniSpikeDown::update()
{
	drawSelf();
}

void MiniSpikeLeft::create()
{
	depth = 0;
	setSprite("mini_spike_left");
	addCollision(Index::Killer);
}

void MiniSpikeLeft::update()
{
	drawSelf();
}

void MiniSpikeRight::create()
{
	depth = 0;
	setSprite("mini_spike_right");
	addCollision(Index::Killer);
}

void MiniSpikeRight::update()
{
	drawSelf();
}

void MiniSpikeUp::create()
{
	depth = 0;
	setSprite("mini_spike_up");
	addCollision(Index::Killer);
}

void MiniSpikeUp::update()
{
	drawSelf();
}

void Platform::create()
{
	depth = 10;
	setSprite("platform");
	addCollision(Index::Platform);
}

void Platform::update()
{
	drawSelf();
}

#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))

void Player::create()
{
	depth = -10;
	imageSpeed = 0.2f;
	gravity = 0.4f * PlayerMgr.grav;

	setSprite("player_idle");
	setMask("player_mask");
	setOrigin(17, 23, true);
	addCollision(Index::Player);

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

	// dotkid check
	if (PlayerMgr.dotkid)
	{
		setSprite("dotkid");
		setOrigin(16, 8);
	}
	else if (!PlayerMgr.dotkid)
	{
		setSprite("idle", false);
		setOrigin(17, 23);

		if (PlayerMgr.grav == 1)
		{
			setMask("player_mask");
		}
		else
		{
			setMask("player_mask_flip");
			setMaskOrigin(17, 8);
		}
	}

	auto normalXorigin = 17;
	auto normalYorigin = 23;
	auto slideXorigin = 7;
	auto slideYorigin = 10;
	if (PlayerMgr.dotkid)
	{
		normalXorigin = 16;
		normalYorigin = 8;
		slideXorigin = 16;
		slideYorigin = 8;
	}

	auto L = InputMgr.isKeyHold(sf::Keyboard::Left);
	auto R = InputMgr.isKeyHold(sf::Keyboard::Right);

	float h = 0;
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
		imageSpeed = 0.2f;
	}
	hspeed = maxHspeed * h;
	if (!onPlatform)
	{
		if (vspeed * PlayerMgr.grav < -0.05f)
		{
			setSprite("player_jump", false);
			setOrigin(normalXorigin, normalYorigin, false);
		}
		else if (vspeed * PlayerMgr.grav > 0.05f)
		{
			setSprite("player_fall", false);
			setOrigin(normalXorigin, normalYorigin, false);
		}
	}
	if (!placeMeeting(x, y + 4 * PlayerMgr.grav, Index::Platform))
	{
		onPlatform = false;
	}

	if (abs(vspeed) > maxVspeed)
	{
		vspeed = sign(vspeed) * maxVspeed;
	}

	auto water = placeMeeting(x, y, Index::Water);
	auto water2 = placeMeeting(x, y, Index::Water2);
	auto water3 = placeMeeting(x, y, Index::Water3);

	if (water || water2 || water3)
	{
		vspeed = min(vspeed * PlayerMgr.grav, 2.0f) * PlayerMgr.grav;

		if (!water2)
		{
			djump = true;
		}
	}

	if (InputMgr.isKeyPress(sf::Keyboard::Z))
	{
		if (ObjMgr.getCount(GetIndex(PlayerBullet)) < 4) 
		{
			ResMgr.sounds["shoot"]->play();

			auto by = y;
			if (PlayerMgr.dotkid)
				by = y + 6;

			auto b = Create(GetIndex(PlayerBullet), x, by);
			b->hspeed = PlayerMgr.face * 16;
		}
	}

	if (InputMgr.isKeyPress(sf::Keyboard::LShift) || InputMgr.isKeyPress(sf::Keyboard::RShift))
	{
		if (placeMeeting(x, y + 1 * PlayerMgr.grav, Index::Block) || placeMeeting(x, y + 1 * PlayerMgr.grav, Index::Block) || onPlatform ||
			water)
		{
			ResMgr.sounds["jump"]->play();
			vspeed = -jump * PlayerMgr.grav;
			djump = true;
		}
		else if (djump || water2 || PlayerMgr.infjump)
		{
			ResMgr.sounds["djump"]->play();
			setSprite("player_jump", false);
			setOrigin(normalXorigin, normalYorigin, false);
			vspeed = -jump2 * PlayerMgr.grav;
			if (!water3)
				djump = false;
			else djump = true;
		}
	}

	if (InputMgr.isKeyRelease(sf::Keyboard::LShift)|| InputMgr.isKeyRelease(sf::Keyboard::RShift))
	{
		if (vspeed * PlayerMgr.grav < 0)
		{
			vspeed *= 0.45f;
		}
	}

	// vine
	auto notOnBlock = !placeMeeting(x, y + 1 * PlayerMgr.grav, Index::Block);
	auto onVineL = placeMeeting(x - 1, y, Index::WalljumpL) && notOnBlock;
	auto onVineR = placeMeeting(x + 1, y, Index::WalljumpR) && notOnBlock;
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
		setOrigin(slideXorigin, slideYorigin, false);
		imageSpeed = 0.5;

		if ((onVineL && InputMgr.isKeyPress(sf::Keyboard::Right)) || (onVineR && InputMgr.isKeyPress(sf::Keyboard::Left)))
		{
			if (InputMgr.isKeyHold(sf::Keyboard::LShift) || InputMgr.isKeyHold(sf::Keyboard::RShift))
			{
				ResMgr.sounds["walljump"]->play();
				if (onVineR) hspeed = -15;
				else hspeed = 15;
				vspeed = -9 * PlayerMgr.grav;
				setSprite("player_jump", false);
				setOrigin(normalXorigin, normalYorigin, false);
			}
			else
			{
				if (onVineR) hspeed = -3;
				else hspeed = 3;
				setSprite("player_fall", false);
				setOrigin(normalXorigin, normalYorigin, false);
			}
		}
	}

	// movement
	vspeed += gravity;
	x += hspeed;
	y += vspeed;

	// block
	auto dir = 0;
	if (placeMeeting(x, y, Index::Block))
	{
		x = xprevious;
		y = yprevious;

		if (placeMeeting(x + hspeed, y, Index::Block))
		{
			moveContact(hspeed, 0, Index::Block);

			hspeed = 0;
		}
		if (placeMeeting(x, y + vspeed, Index::Block))
		{
			moveContact(0, vspeed, Index::Block);

			if (vspeed * PlayerMgr.grav > 0)
			{
				djump = true;
			}
			vspeed = 0;
		}
		if (placeMeeting(x + hspeed, y + vspeed, Index::Block))
		{
			hspeed = 0;
		}

		x += hspeed;
		y += vspeed;
	}

	// platform
	auto pf = placeMeeting(x, y, Index::Platform);
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
		gravity = 0.4f * PlayerMgr.grav;
		djump = true;
		vspeed = 0;

		if (!PlayerMgr.dotkid) 
		{
			if (PlayerMgr.grav == 1)
			{
				setMask("player_mask");
				setMaskOrigin(17, 23);
			}
			else
			{
				setMask("player_mask_flip");
				setMaskOrigin(17, 8);
			}
		}
		else 
		{
			if (PlayerMgr.grav == 1)
			{
				setMaskOrigin(16, 8);
			}
			else
			{
				setMaskOrigin(16, 24);
			}
		}
		y += 4 * PlayerMgr.grav;
	};

	// gravity arrow
	if (PlayerMgr.grav == 1 && placeMeeting(x, y, Index::GravityArrowUp))
	{
		flipGrav();
	}

	if (PlayerMgr.grav == -1 && placeMeeting(x, y, Index::GravityArrowDown))
	{
		flipGrav();
	}

	// killer
	if (placeMeeting(x, y, Index::Killer))
	{
		for (auto i = 0; i < 200; i++)
		{
			Create(GetIndex(Blood), x, y);
		}
		ResMgr.sounds["death"]->play();
		DestroyByName(Player);
		PlayerMgr.player = nullptr;
		return;
	}

	updateSprite();

	if (!PlayerMgr.dotkid)
	{
		if (PlayerMgr.showMask == ShowMask::OnlyPlayer)
		{
			sprite->draw(FloorToInt(imageIndex), x, y, xorigin, yorigin, PlayerMgr.face, PlayerMgr.grav, rotation, color);
		}
		else if (PlayerMgr.showMask == ShowMask::OnlyMask)
		{
			drawMask();
		}
		else
		{
			auto col = sf::Color::White;
			col.a = 120;
			sprite->draw(FloorToInt(imageIndex), x, y, xorigin, yorigin, PlayerMgr.face, PlayerMgr.grav, rotation, col);
			maskSprite->draw(FloorToInt(imageIndex), x, y, maskXorigin, maskYorigin, 1, 1, rotation, col);
		}
	}
	else
	{
		drawMask();
		if (PlayerMgr.dotkidOutline)
		{
			ResMgr.sprites["dotkid_outline"]->draw(0, x, y + 8, 24, 24, 1, 1, 0, sf::Color::White);
		}
	}
}

void PlayerStart::create()
{
	for (auto const& o : ObjMgr.objects)
	{
		if (o->index == index && o.get() != this)
			Destroy(o);
	}
	DestroyByName(Player);
	Create(GetIndex(Player), x + 17, y + 23);
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
	addCollision(Index::Save);
}

void Save::update()
{
	drawSelf();
}

void SpikeDown::create()
{
	depth = 0;
	setSprite("spike_down");
	addCollision(Index::Killer);
}

void SpikeDown::update()
{
	drawSelf();
}

void SpikeLeft::create()
{
	depth = 0;
	setSprite("spike_left");
	addCollision(Index::Killer);
}

void SpikeLeft::update()
{
	drawSelf();
}

void SpikeRight::create()
{
	depth = 0;
	setSprite("spike_right");
	addCollision(Index::Killer);
}

void SpikeRight::update()
{
	drawSelf();
}

void SpikeUp::create()
{
	depth = 0;
	setSprite("spike_up");
	addCollision(Index::Killer);
}

void SpikeUp::update()
{
	drawSelf();
}

void WalljumpL::create()
{
	depth = -1;
	setSprite("walljump_l");
	addCollision(Index::WalljumpL);
}

void WalljumpL::update()
{
	drawSelf();
}

void WalljumpR::create()
{
	depth = -1;
	setSprite("walljump_r");
	addCollision(Index::WalljumpR);
}

void WalljumpR::update()
{
	drawSelf();
}

void Warp::create()
{
	depth = 0;
	setSprite("warp");
	addCollision(Index::Warp);
}

void Warp::update()
{
	drawSelf();
}

void Water::create()
{
	depth = -50;
	setSprite("water");
	addCollision(Index::Water);
}

void Water::update()
{
	drawSelf();
}

void Water2::create()
{
	depth = -50;
	setSprite("water2");
	addCollision(Index::Water2);
}

void Water2::update()
{
	drawSelf();
}


void Water3::create()
{
	depth = -50;
	setSprite("water3");
	addCollision(Index::Water3);
}

void Water3::update()
{
	drawSelf();
}


void GravityArrowUp::create()
{
	depth = 0;
	setSprite("gravity_up");
	addCollision(Index::GravityArrowUp);
}

void GravityArrowUp::update()
{
	drawSelf();
}


void GravityArrowDown::create()
{
	depth = 0;
	setSprite("gravity_down");
	addCollision(Index::GravityArrowDown);
}

void GravityArrowDown::update()
{
	drawSelf();
}

void Blood::create()
{
	depth = -5;

	imageIndex = Random::get(0.0f, 2.0f);
	imageSpeed = 0;
	gravity = (0.1f + Random::get(0.0f, 0.2f)) * PlayerMgr.grav;
	auto direction = Random::get(0.0f, PI * 2);

	auto speed = Random::get(0.0f, 6.0f);
	hspeed = speed * cos(direction);
	vspeed = speed * sin(direction);

	xscale = 1.5;
	yscale = xscale;
	setSprite("blood");
	setOrigin(2, 2);
	addCollision(Index::Blood);
}

void Blood::update()
{
	xprevious = x;
	yprevious = y;

	vspeed += gravity;

	x += hspeed;
	y += vspeed;

	if (placeMeeting(x, y, Index::Block))
	{
		x = xprevious;
		y = yprevious;

		moveContact(hspeed, vspeed, Index::Block);

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

void PlayerBullet::create()
{
	depth = -1;
	timer = 40;
	imageSpeed = 1;
	setSprite("bullet");
	setOrigin(1, 1);
	addCollision(Index::Save);
}

void PlayerBullet::update()
{
	x += hspeed;

	if (--timer == 0)
	{
		DestroyThis();
		return;
	}

	if (x < 0 || x > 800)
	{
		DestroyThis();
		return;
	}

	if (placeMeeting(x, y, Index::Block) != nullptr)
	{
		DestroyThis();
		return;
	}

	drawSelf();
}