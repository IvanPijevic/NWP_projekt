#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <Engine/SpriteBatch.h>
#include <Engine/ResourceManager.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Background
{
public:
	void init(Engine::SpriteBatch& spriteBatch);
	void draw(Engine::SpriteBatch& spriteBatch, float positionX, float positionY);
	void coverBackground(int screenWidth, int screenHeight, Engine::SpriteBatch& spriteBatch);

private:
	Engine::Texture m_backgroundTexture;
	Engine::ColorRGBA8 m_color;
};

#endif