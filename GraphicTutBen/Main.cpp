#include <SDL/SDL_main.h>
#include <SDL/SDL.h>

#include "System.h"


#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	System system;
	system.Run();

	return 0;
}