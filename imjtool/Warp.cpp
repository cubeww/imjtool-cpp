#include "Warp.h"

Warp::Warp()
{
	setSprite("warp");
}

void Warp::update()
{
	drawSelf();
}
