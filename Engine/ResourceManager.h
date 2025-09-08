#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "TextureCache.h"
#include <string>

namespace Engine
{

	class ResourceManager
	{
	public:
		static Texture getTexture(std::string texturePath);
		static GLuint boundTexture;

	private:
		static TextureCache m_textureCache;
	};
}
#endif  //RESOURCEMANAGER_H