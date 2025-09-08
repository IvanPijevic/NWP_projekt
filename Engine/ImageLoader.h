#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <string>

#include "Texture.h"
#include "PicoPNG.h"
#include "IOManager.h"
#include "Error.h"

namespace Engine
{

	class ImageLoader
	{
	public:

		static Texture loadPNG(std::string filePath);
	};
}
#endif  //IMAGELOADER_H