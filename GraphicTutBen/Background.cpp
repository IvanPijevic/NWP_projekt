#include "Background.h"

Background::Background()
{}

Background::~Background()
{}

void Background::init(Engine::SpriteBatch& spriteBatch, int screenWidth, int screenHeight)
{
	//Init Background
	m_backgroundTexture = Engine::ResourceManager::getTexture("Textures/Backgrounds/black.png");

	m_color = Engine::ColorRGBA8(255, 255, 255, 255);
}

void Background::draw(Engine::SpriteBatch& spriteBatch, float positionX, float positionY)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 positionAndDimension(positionX, positionY, m_backgroundTexture.width, m_backgroundTexture.height);

	spriteBatch.draw(positionAndDimension, uv, m_backgroundTexture.id, 0.0f, m_color);
}

void Background::coverBackground(int screenWidth, int screenHeight, Engine::SpriteBatch& spriteBatch)
{
	int widthScreenFields = screenWidth / m_backgroundTexture.width;
	int heightScreenFields = screenHeight / m_backgroundTexture.height;

	float posX = -(screenWidth / 2);
	float posY = -(screenHeight / 2);

	for (int i = 0; i < heightScreenFields;)
	{
		for (int j = 0; j < widthScreenFields; j++)
		{
			draw(spriteBatch, posX, posY);

			posX += m_backgroundTexture.width;
		}

		posX = -(screenWidth / 2);
		posY += m_backgroundTexture.height;

		i++;
	}
}