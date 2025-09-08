#ifndef WINDOW_H
#define WINDOW_H

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

#include "Error.h"

namespace Engine
{

	enum WindowFlags { INVISIBLE = 0x1, FULL_SCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		void swapBuffer();

		//Getters
		int getScreenWidth() { m_screenWidth; }
		int getScreenHeight() { m_screenHeight; }

	private:
		SDL_Window* m_window;

		int m_screenWidth;
		int m_screenHeight;
	};
}
#endif  //WINDOW_H