#include "Game.h"
#include <windows.h>

#ifdef IMJTOOL_DEBUG
int main()
{
	Gm.run();
}
#else
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	Gm.run();
}
#endif