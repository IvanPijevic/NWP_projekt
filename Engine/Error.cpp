#include "Error.h"

#include <cstdlib>

namespace Engine
{

	void fatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		std::cout << "Enter any hey to quit...";
		int temp;
		std::cin >> temp;

		SDL_Quit();
		exit(3);
	}

}