#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

namespace Engine
{

	struct Texture
	{
		GLuint id;
		int width;
		int height;
	};
}
#endif  //TEXTURE_H