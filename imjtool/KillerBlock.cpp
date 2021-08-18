#include "KillerBlock.h"

KillerBlock::KillerBlock()
{
	setSprite("killer_block");
}

void KillerBlock::update()
{
	drawSelf();
}
