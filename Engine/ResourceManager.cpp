#include "ResourceManager.h"

namespace Engine
{

	TextureCache ResourceManager::m_textureCache;

	Texture ResourceManager::getTexture(std::string texturePath)
	{
		return m_textureCache.getTexture(texturePath);
	}

}