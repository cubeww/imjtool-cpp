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
	case Index::BulletBlocker:
		return true;
	default:
		return false;
	}
}

bool isSkinable(int index)
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
	case Index::BulletBlocker:
	case Index::Bg:
	case Index::SaveEffect:
		return true;
	default:
		return false;
	}
}

string spriteOf(int index)
{
	switch (static_cast<Index>(index))
	{
	case Index::SpikeUp: return "spike_up";
	case Index::SpikeDown: return "spike_down";
	case Index::SpikeLeft: return "spike_left";
	case Index::SpikeRight: return "spike_right";
	case Index::MiniSpikeUp: return "mini_spike_up";
	case Index::MiniSpikeDown: return "mini_spike_down";
	case Index::MiniSpikeLeft: return "mini_spike_left";
	case Index::MiniSpikeRight: return "mini_spike_right";
	case Index::Block: return "block";
	case Index::MiniBlock: return "mini_block";
	case Index::Apple: return "apple";
	case Index::Save: return "save";
	case Index::Platform: return "platform";
	case Index::KillerBlock: return "killer_block";
	case Index::Water: return "water";
	case Index::Water2: return "water2";
	case Index::Water3: return "water3";
	case Index::WalljumpL: return "walljump_l";
	case Index::WalljumpR: return "walljump_r";
	case Index::PlayerStart: return "player_start";
	case Index::Warp: return "warp";
	case Index::JumpRefresher: return "jump_refresher";
	case Index::GravityArrowUp: return "gravity_up";
	case Index::GravityArrowDown: return "gravity_down";
	case Index::BulletBlocker: return "bullet_blocker";
	case Index::Bg: return "bg";
	case Index::SaveEffect: return "save";
	}
	return "undefined";
}


void Apple::create()
{
	depth = 0;
	imageSpeed = 1.0f / 15.0f;
	setMask("apple");
	applySkin();
	addCollision(Index::Killer);
}

void Apple::update()
{
	imageIndex += imageSpeed;
	drawSelf();
}

void Block::create()
{
	depth = 1;
	setMask("block");
	applySkin();
	addCollision(Index::Block);
}

void Block::update()
{
	drawSelf();
}

void MiniBlock::create()
{
	depth = 1;
	setMask("mini_block");
	applySkin();
	addCollision(Index::Block);
}

void MiniBlock::update()
{
	drawSelf();
}

void JumpRefresher::create()
{
	depth = 0;
	setMask("jump_refresher");
	applySkin();
	addCollision(Index::JumpRefresher);
}

void JumpRefresher::update()
{
	drawSelf();
}

void KillerBlock::create()
{
	depth = 0;
	setMask("killer_block");
	applySkin();
	addCollision(Index::Killer);
}

void KillerBlock::update()
{
	drawSelf();
}

void MiniSpikeDown::create()
{
	depth = 0;
	setMask("mini_spike_down");
	applySkin();
	addCollision(Index::Killer);
}

void MiniSpikeDown::update()
{
	imageIndex += imageSpeed;
	drawSelf();
}

void MiniSpikeLeft::create()
{
	depth = 0;
	setMask("mini_spike_left");
	applySkin();
	addCollision(Index::Killer);
}

void MiniSpikeLeft::update()
{
	imageIndex += imageSpeed;
	drawSelf();
}

void MiniSpikeRight::create()
{
	depth = 0;
	setMask("mini_spike_right");
	applySkin();
	addCollision(Index::Killer);
}

void MiniSpikeRight::update()
{
	imageIndex += imageSpeed;
	drawSelf();
}

void MiniSpikeUp::create()
{
	depth = 0;
	setMask("mini_spike_up");
	applySkin();
	addCollision(Index::Killer);
}

void MiniSpikeUp::update()
{
	imageIndex += imageSpeed;
	drawSelf();
}

void Platform::create()
{
	depth = 10;
	setMask("platform");
	applySkin();
	addCollision(Index::Platform);
}

void Platform::update()
{
	drawSelf();
}

void Player::create()
{
	depth = -10;
	imageSpeed = 0.2f;
	gravity = 0.4f * PlayerMgr.grav;

	setSprite("player_idle");
	setMask("player_mask");
	addCollision(Index::Player);

	PlayerMgr.player = static_pointer_cast<Player>(weakPtr.lock());
}

void Player::update()
{
	xprevious = x;
	yprevious = y;

	PlayerMgr.frameActionJump = false;
	PlayerMgr.frameActionDjump = false;
	PlayerMgr.frameActionJumpSlow = false;

	// dotkid check
	if (PlayerMgr.dotkid)
	{
		setSprite("dotkid");
	}
	else if (!PlayerMgr.dotkid)
	{
		setSprite("idle", false);

		if (PlayerMgr.grav == 1)
		{
			setMask("player_mask");
		}
		else
		{
			setMask("player_mask_flip");
		}
	}

	auto L = InputMgr.isKeyHoldG(sf::Keyboard::Left);
	auto R = InputMgr.isKeyHoldG(sf::Keyboard::Right);

	float h = 0;
	if (R) h = 1;
	else if (L) h = -1;

	if (h != 0)
	{
		PlayerMgr.face = h;
		setSprite("player_running", false);
		imageSpeed = 0.5;
	}
	else
	{
		setSprite("player_idle", false);
		imageSpeed = 0.2f;
	}
	hspeed = maxHspeed * h;
	if (!onPlatform)
	{
		if (vspeed * PlayerMgr.grav < -0.05f)
		{
			setSprite("player_jump", false);
		}
		else if (vspeed * PlayerMgr.grav > 0.05f)
		{
			setSprite("player_fall", false);
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

	// shoot
	if (InputMgr.isKeyPressG(sf::Keyboard::Z))
	{
		if (ObjMgr.getCount(GetIndex(PlayerBullet)) < 4)
		{
			ResMgr.sounds["shoot"]->play();

			auto by = y;
			if (PlayerMgr.dotkid)
				by = y + 6;

			auto b = CreateInst(GetIndex(PlayerBullet), x, by);
			b->hspeed = PlayerMgr.face * 16;
		}
	}

	// jump press
	if (InputMgr.isKeyPressG(sf::Keyboard::LShift) || InputMgr.isKeyPressG(sf::Keyboard::RShift))
	{
		if (placeMeeting(x, y + 1 * PlayerMgr.grav, Index::Block) || placeMeeting(
				x, y + 1 * PlayerMgr.grav, Index::Platform) || onPlatform ||
			water)
		{
			ResMgr.sounds["jump"]->play();
			vspeed = -jump * PlayerMgr.grav;
			djump = true;
			PlayerMgr.frameActionJump = true;
		}
		else if (djump || water2 || PlayerMgr.infjump)
		{
			ResMgr.sounds["djump"]->play();
			setSprite("player_jump", false);
			vspeed = -jump2 * PlayerMgr.grav;
			if (!water3)
				djump = false;
			else djump = true;
			PlayerMgr.frameActionDjump = true;
		}
	}

	// jump release
	if (InputMgr.isKeyReleaseG(sf::Keyboard::LShift) || InputMgr.isKeyReleaseG(sf::Keyboard::RShift))
	{
		if (vspeed * PlayerMgr.grav < 0)
		{
			vspeed *= 0.45f;
			PlayerMgr.frameActionJumpSlow = true;
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
		imageSpeed = 0.5;

		if ((onVineL && InputMgr.isKeyPressG(sf::Keyboard::Right)) || (onVineR && InputMgr.
			isKeyPressG(sf::Keyboard::Left)))
		{
			if (InputMgr.isKeyHoldG(sf::Keyboard::LShift) || InputMgr.isKeyHoldG(sf::Keyboard::RShift))
			{
				ResMgr.sounds["walljump"]->play();
				if (onVineR) hspeed = -15;
				else hspeed = 15;
				vspeed = -9 * PlayerMgr.grav;
				setSprite("player_jump", false);
			}
			else
			{
				if (onVineR) hspeed = -3;
				else hspeed = 3;
				setSprite("player_fall", false);
			}
		}
	}

	// A / D adjust
	if (placeMeeting(x, y + PlayerMgr.grav, Index::Block))
	{
		if (InputMgr.isKeyPressG(sf::Keyboard::A))
		{
			hspeed = -1;
		}
		if (InputMgr.isKeyPressG(sf::Keyboard::D))
		{
			hspeed = 1;
		}
	}

	// press S save
	if (InputMgr.isKeyPressG(sf::Keyboard::S))
	{
		ResMgr.sounds["shoot"]->play();
		CreateInst(GetIndex(SaveEffect), x - 17, y - 23);
		PlayerMgr.save();
	}

	// movement
	vspeed += gravity;
	x += hspeed;
	y += vspeed;

	// block
	auto block = placeMeeting(x, y, Index::Block);
	if (block != nullptr)
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
			}
			else
			{
				setMask("player_mask_flip");
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
	auto killer = placeMeeting(x, y, Index::Killer);
	if (killer != nullptr)
	{
		killer->setHighlight();
		if (PlayerMgr.deathEnable) 
		{
			kill();
			return;
		}
	}

	// border
	if (x < 0 || x > 800 || y < 0 || y > 608)
	{
		kill();
		return;
	}

	// analysis
	PlayerMgr.doAnalysis();

	updateSprite();

	drawPlayer();
}

void Player::drawPlayer()
{
	if (!PlayerMgr.dotkid)
	{
		if (PlayerMgr.showMask == ShowMask::OnlyPlayer)
		{
			sprite->draw(FloorToInt(imageIndex), x, y, sprite->xOrigin, sprite->yOrigin, PlayerMgr.face, PlayerMgr.grav,
				rotation, color);
		}
		else if (PlayerMgr.showMask == ShowMask::OnlyMask)
		{
			drawMask();
		}
		else
		{
			auto col = sf::Color::White;
			col.a = 120;
			sprite->draw(FloorToInt(imageIndex), x, y, sprite->xOrigin, sprite->yOrigin, PlayerMgr.face, PlayerMgr.grav,
				rotation, col);
			maskSprite->draw(FloorToInt(imageIndex), x, y, maskSprite->xOrigin, maskSprite->yOrigin, 1, 1, rotation,
				col);
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


void Player::kill()
{
	for (auto i = 0; i < 200; i++)
	{
		CreateInst(GetIndex(Blood), x, y);
	}
	ResMgr.sounds["death"]->play();
	DestroyByName(Player);
}


void PlayerStart::create()
{
	for (const auto& o : ObjMgr.objects)
	{
		if (o->index == index && o.get() != this)
			DestroyInst(o);
	}
	DestroyByName(Player);
	DestroyByName(Blood);
	CreateInst(GetIndex(Player), x + 17, y + 23);
	depth = 0;
	setMask("player_start");
	applySkin();
	PlayerMgr.save();
}

void PlayerStart::update()
{
	drawSelf();
}

void Save::create()
{
	depth = 0;
	setMask("save");
	applySkin();
	addCollision(Index::Save);
}

void Save::update()
{
	if (--timer == 0)
		canSave = true;

	if (--timer2 == 0)
		imageIndex = 0;

	auto press = InputMgr.isKeyPressG(sf::Keyboard::Z);
	auto enter = placeMeeting(x, y, Index::Player);
	if (PlayerMgr.saveType == SaveType::OnlyShoot)
	{
		if (enter && press)
		{
			save();
		}
	}
	else
	{
		if ((enter && press) || placeMeeting(x, y, Index::PlayerBullet))
		{
			save();
		}
	}

	drawSelf();
}

void Save::save()
{
	timer = 30;
	timer2 = 59;
	imageIndex = 1;
	canSave = false;
	PlayerMgr.save();
}


void SpikeDown::create()
{
	depth = 0;
	setMask("spike_down");
	applySkin();
	addCollision(Index::Killer);
}

void SpikeDown::update()
{
	imageIndex += imageSpeed;
	drawSelf();
}

void SpikeLeft::create()
{
	depth = 0;
	setMask("spike_left");
	applySkin();
	addCollision(Index::Killer);
}

void SpikeLeft::update()
{
	imageIndex += imageSpeed;
	drawSelf();
}

void SpikeRight::create()
{
	depth = 0;
	setMask("spike_right");
	applySkin();
	addCollision(Index::Killer);
}

void SpikeRight::update()
{
	imageIndex += imageSpeed;
	drawSelf();
}

void SpikeUp::create()
{
	depth = 0;
	setMask("spike_up");
	applySkin();
	addCollision(Index::Killer);
}

void SpikeUp::update()
{
	imageIndex += imageSpeed;
	drawSelf();
}

void WalljumpL::create()
{
	depth = -1;
	setMask("walljump_l");
	applySkin();
	addCollision(Index::WalljumpL);
}

void WalljumpL::update()
{
	drawSelf();
}

void WalljumpR::create()
{
	depth = -1;
	setMask("walljump_r");
	applySkin();
	addCollision(Index::WalljumpR);
}

void WalljumpR::update()
{
	drawSelf();
}

void Warp::create()
{
	depth = 0;
	setMask("warp");
	applySkin();
	addCollision(Index::Warp);
}

void Warp::update()
{
	auto player = placeMeeting(x, y, Index::Player);
	if (player != nullptr)
	{
		DestroyInst(player);
	}

	drawSelf();
}

void Water::create()
{
	depth = -50;
	setMask("water");
	applySkin();
	addCollision(Index::Water);
}

void Water::update()
{
	drawSelf();
}

void Water2::create()
{
	depth = -50;
	setMask("water2");
	applySkin();
	addCollision(Index::Water2);
}

void Water2::update()
{
	drawSelf();
}


void Water3::create()
{
	depth = -50;
	setMask("water3");
	applySkin();
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
	addCollision(Index::PlayerBullet);
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

	if (placeMeeting(x, y, Index::Block) != nullptr || placeMeeting(x, y, Index::Platform) != nullptr || placeMeeting(
		x, y, Index::BulletBlocker) != nullptr)
	{
		DestroyThis();
		return;
	}

	drawSelf();
}

void BulletBlocker::create()
{
	depth = 0;

	setMask("bullet_blocker");
	applySkin();
	addCollision(Index::BulletBlocker);
}

void BulletBlocker::update()
{
	drawSelf();
}

void Bg::create()
{
	depth = 100;
	for (auto i = 0; i < 10; i++)
	{
		rects[i] = sf::RectangleShape(sf::Vector2f(800, 608));
		rects[i].setTextureRect(sf::Rect(0, 0, 800, 608));
	}

	rects[0].setPosition(-800, -608);
	rects[1].setPosition(0, -608);
	rects[2].setPosition(800, -608);

	rects[3].setPosition(-800, 0);
	rects[4].setPosition(0, 0);
	rects[5].setPosition(800, 0);

	rects[6].setPosition(-800, 608);
	rects[7].setPosition(0, 608);
	rects[8].setPosition(800, 608);

	applySkin();
}

void Bg::update()
{
	auto tex = sprite->items[0]->sprite->getTexture();

	auto cycleNum = [](int v, int vmin, int vmax)
	{
		return (v - vmin + (1 + abs(v)) * (vmax - vmin)) % (vmax - vmin) + vmin;
	};

	hspeed = SkinMgr.curSkin->hspeed;
	vspeed = SkinMgr.curSkin->vspeed;

	if (SkinMgr.curSkin->bgType == BgType::Stretch)
	{
		x = cycleNum(FloorToInt(x + hspeed), 0, 800);
		y = cycleNum(FloorToInt(y + vspeed), 0, 608);

		rects[0].setPosition(x - 800, y - 608);
		rects[1].setPosition(x, y - 608);
		rects[2].setPosition(x + 800, y - 608);

		rects[3].setPosition(x - 800, y);
		rects[4].setPosition(x, y);
		rects[5].setPosition(x + 800, y);

		rects[6].setPosition(x - 800, y + 608);
		rects[7].setPosition(x, y + 608);
		rects[8].setPosition(x + 800, y + 608);

		for (auto i = 0; i < 9; i++)
		{
			rects[i].setTexture(tex);
			Gm.gameTexture->draw(rects[i]);
		}
	}
	else
	{
		rects[9].setTexture(tex);
		auto size = tex->getSize();

		x = cycleNum(FloorToInt(x + hspeed), 0, size.x);
		y = cycleNum(FloorToInt(y + vspeed), 0, size.y);

		rects[9].setTextureRect(sf::IntRect(0, 0, 800 + size.x, 608 + size.y));
		rects[9].setSize(sf::Vector2f(800 + size.x, 608 + size.y));
		rects[9].setPosition(x - size.x, y - size.y);
		Gm.gameTexture->draw(rects[9]);
	}
}

void Grid::create()
{
	depth = 99;
}

void Grid::update()
{
	if (Gm.gui.showGrid)
	{
		if (Gm.gui.gridTexture != nullptr)
		{
			auto col = sf::Color::White;
			col.a = 50;
			grid.setColor(col);
			grid.setTexture(Gm.gui.gridTexture->getTexture());
			Gm.gameTexture->draw(grid);
		}
	}
}

void BorderBlock::create()
{
	setMask(spriteOf(GetIndex(Block)));
	addCollision(Index::Block);
}

void BorderBlock::update()
{
	if (PlayerMgr.deathBorder == DeathBorder::Solid)
	{
		addCollision(Index::Block);
	}
	else
	{
		removeCollision(Index::Block);
	}
}

void SaveEffect::create()
{
	depth = -1;
	applySkin();
}

void SaveEffect::update()
{
	imageIndex = 1;
	color.a -= 26;
	if (color.a <= 26)
	{
		DestroyThis();
		return;
	}

	drawSelf();
}

