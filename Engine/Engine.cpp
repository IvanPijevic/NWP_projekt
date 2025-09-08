#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Engine.h"

namespace Engine
{

	int init()
	{
		//Init SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//Tell OpenGL we want double buffered window
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}

}