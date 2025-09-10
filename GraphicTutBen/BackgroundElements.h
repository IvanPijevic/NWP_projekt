#ifndef BACKGROUND_ELEMENTS_H
#define BACKGROUND_ELEMENTS_H

#include <Engine/SpriteBatch.h>
#include <Engine/ResourceManager.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>

class BackgroundElements
{
public:
	BackgroundElements();
	~BackgroundElements();

	void init();
	void pickStarPosition(int screenWidth, int screenHeight);
	void updateBackground(float deltaTime, int screenHeight);
	void randomStarTexture();
	void drawStars(Engine::SpriteBatch& spriteBatch);

private:
	std::vector<Engine::Texture> m_stars;
	std::vector<glm::vec2> m_starPosition;
	std::vector<int> m_starID;

	Engine::Texture m_textureMainMenu;

	Engine::ColorRGBA8 m_color;

	int m_numberOfStars;
	int m_screenBorderStarOffset;

	float m_starSpeed;

};

#endif 