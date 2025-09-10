#include "TextureCache.h"

namespace Engine
{

	TextureCache::TextureCache()
	{

	}

	TextureCache::~TextureCache()
	{

	}

	Texture TextureCache::getTexture(std::string texturePath)
	{
		//Look up the texture and see if its in the map
		std::map<std::string, Texture>::iterator mit = m_textureMap.find(texturePath);

		//Check if its not in the map
		if (mit == m_textureMap.end())
		{
			//Load texture
			Texture newTexture = ImageLoader::loadPNG(texturePath);

			//Insert it in the map
			m_textureMap.insert(make_pair(texturePath, newTexture));

			return newTexture;
		}

		return mit->second;
	}

}