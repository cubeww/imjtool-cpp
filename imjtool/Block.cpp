#include "Block.h"

Block::Block()
{
	setSprite("block");
}

void Block::update()
{
	drawSelf();
}
