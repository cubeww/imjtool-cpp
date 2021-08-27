#include "PlayerManager.h"
#include "InGame.h"

void PlayerManager::update()
{
	if (InputMgr.isKeyPress(sf::Keyboard::R))
	{
		load();
	}
}

void PlayerManager::save()
{
	if (!player.expired())
	{
		currentSave.x = player.lock()->x;
		currentSave.y = player.lock()->y;
		currentSave.grav = grav;
		currentSave.face = face;
	}
}

void PlayerManager::load()
{
	DestroyByName(Player);
	DestroyByName(Blood);

	CreateInst(GetIndex(Player), currentSave.x, currentSave.y);

	player.lock()->x = currentSave.x;
	player.lock()->y = currentSave.y;
	grav = currentSave.grav;
	face = currentSave.face;
}

void PlayerManager::doAnalysis()
{
	if (!player.expired())
	{
		auto p = player.lock();
		// analysis: position
		x = p->x;
		y = p->y;

		// analysis: jump
		jumpCount++;
		bool playerOnGround = p->placeMeeting(x, y + grav, Index::Block) != nullptr;
		if (frameActionJump)
		{
			jumpState = JumpState::FirstHold;
			frameCountJump1 = 0;
			frameCountPause = 0;
			frameCountJump2 = 0;
			frameCountPause2 = 0;
			jumpCount = 1;
		}
		else if (frameActionDjump)
		{
			if (jumpState == JumpState::FirstHold)
			{
				frameCountJump1 = jumpCount;
			}
			else if (jumpState == JumpState::FirstWait)
			{
				frameCountPause = jumpCount;
			}
			jumpState = JumpState::SecondHold;
			jumpCount = 1;
		}
		if (frameActionJumpSlow)
		{
			if (jumpState == JumpState::FirstHold)
			{
				jumpState = JumpState::FirstWait;
				frameCountJump1 = jumpCount;
				jumpCount = 0;
			}
			else if (jumpState == JumpState::SecondHold)
			{
				jumpState = JumpState::SecondWait;
				frameCountJump2 = jumpCount;
			}
		}

		if ((jumpState == JumpState::SecondWait || jumpState == JumpState::FirstWait) &&
			playerOnGround)
		{
			jumpState = JumpState::Done;
			frameCountPause2 = jumpCount + 1;
		}

		if (lastJumpFrameNext)
		{
			lastJumpFrameNext = false;
			if (jumpState == JumpState::FirstHold)
			{
				jumpState = JumpState::FirstWait;
				frameCountJump1 = jumpCount;
			}
			else if (jumpState == JumpState::SecondHold)
			{
				jumpState = JumpState::SecondWait;
				frameCountJump2 = jumpCount;
			}
			jumpCount = 0;
		}

		auto dy = p->y - p->yprevious;
		auto movedDown = (grav == 1 && dy > 0) || (grav == -1 && dy < 0);
		if (movedDown && (jumpState == JumpState::FirstHold || jumpState == JumpState::SecondHold)
			&& !frameActionJumpSlow)
		{
			lastJumpFrameNext = true;
		}

		// analysis: jump cancel
		jcCount++;

		auto leftShift = InputMgr.isKeyHold(sf::Keyboard::LShift);
		auto rightShift = InputMgr.isKeyHold(sf::Keyboard::RShift);
		auto leftShiftPressed = leftShift && !jcLeftShiftLast;
		auto rightShiftPressed = rightShift && !jcRightShiftLast;
		auto leftShiftReleased = !leftShift && jcLeftShiftLast;
		auto rightShiftReleased = !rightShift && jcRightShiftLast;
		if (frameActionJump || frameActionDjump)
		{
			jcShow = false;
			jcSuccessWaitingForRelease = false;
		}

		if ((leftShiftReleased || rightShiftReleased) && !leftShift && !rightShift)
		{
			jcLateWaiting = true;
			jcCount = 0;
		}
		if (jcLateWaiting)
		{
			if (jcCount > jcCutOff)
			{
				jcLateWaiting = false;
			}
			else if (leftShiftPressed || rightShiftPressed)
			{
				jcLateWaiting = false;
				jcDuration = -jcCount;
				jcShow = true;
			}
		}

		if (leftShift && jcLeftShiftLast && rightShiftPressed)
		{
			jcEarlyWaiting = 1;
			jcCount = 1;
		}
		if (rightShift && jcRightShiftLast && leftShiftPressed)
		{
			jcEarlyWaiting = 2;
			jcCount = 1;
		}
		if (jcEarlyWaiting)
		{
			if (jcCount > jcCutOff)
			{
				jcEarlyWaiting = 0;
			}
			else if ((jcEarlyWaiting == 1 && leftShiftReleased) || (jcEarlyWaiting == 2 && rightShiftReleased))
			{
				jcEarlyWaiting = false;
				jcDuration = jcCount;
				jcShow = true;
			}
		}

		if ((leftShiftReleased && rightShiftPressed) || (rightShiftReleased && leftShiftPressed))
		{
			jcEarlyWaiting = false;
			jcDuration = 1;
			jcShow = true;
		}

		auto eitherJump = frameActionJump || frameActionDjump;
		if (eitherJump && frameActionJumpSlow)
		{
			jcLateWaiting = false;
			jcEarlyWaiting = false;
			jcDuration = 0;
			jcShow = true;
			jcSuccessWaitingForRelease = true;
			jcCount = 0;
		}

		if (jcSuccessWaitingForRelease && frameActionJumpSlow && jcCount > 0)
		{
			jcSuccessDuration = jcCount;
			jcSuccessWaitingForRelease = false;
		}

		jcLeftShiftLast = leftShift;
		jcRightShiftLast = rightShift;
	}
}
