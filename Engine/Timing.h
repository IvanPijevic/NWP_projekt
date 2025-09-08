#ifndef TIMING_H
#define TIMING_H

#include <SDL/SDL.h>

namespace Engine
{

	class FpsLimiter
	{
	public:
		FpsLimiter();

		void init(float maxFPS);
		void setMaxFPS(float maxFPS);

		void begin();
		//End will return the current FPS
		float end();

	private:
		void calculateFPS();

	private:
		float m_fps;
		float m_maxFPS;
		float m_frameTime;

		unsigned int m_startTicks;
	};

}

#endif  //TIMING_H
