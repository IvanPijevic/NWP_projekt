#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>
#include <SDL/SDL.h>

namespace Engine
{

	extern void fatalError(std::string errorString);

}

#endif  //ERROR_H