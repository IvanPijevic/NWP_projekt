#include "BackgroundElements.h"

void BackgroundElements::init()
{
	Engine::Texture m_texture;

	//Init stars
	m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Effects/star1.png");
	m_stars.push_back(m_texture);
	m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Effects/star2.png");
	m_stars.push_back(m_texture);
	m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Effects/star3.png");
	m_stars.push_back(m_texture);

	m_color = Engine::ColorRGBA8(255, 255, 255, 255);
}

void BackgroundElements::pickStarPosition(int screenWidth, int screenHeight)
{
	while (m_starPosition.size() < m_numberOfStars)
	{
		//X coord
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<>  distr(-(screenWidth / 2) + m_screenBorderStarOffset, (screenWidth / 2) - m_screenBorderStarOffset);

		//Y coord
		std::random_device rd1;
		std::mt19937 gen1(rd1());

		std::uniform_int_distribution<> distr1((screenHeight / 2) , screenHeight * 1.5);

		m_starPosition.push_back(glm::vec2(distr(gen), distr1(gen1)));
	}
}

void BackgroundElements::updateBackground(float deltaTime, int screenHeight)

{
	for (int i = 0; i < m_starPosition.size(); i++)
	{
		//Move star down
		m_starPosition[i].y = m_starPosition[i].y - m_starSpeed * deltaTime;

		//If offfscreen delete star
		if (m_starPosition[i].y < (-screenHeight / 2))
		{
			//Delete star type
			m_starID[i] = m_starID.back();
			m_starID.pop_back();

			//Delete star texture
			m_starPosition[i] = m_starPosition.back();
			m_starPosition.pop_back();
		}
	}
}

void BackgroundElements::randomStarTexture()
{
	while (m_starID.size() != m_numberOfStars)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<>  distr(m_stars[0].id, m_stars[2].id);

		m_starID.push_back(distr(gen));
	}
}

void BackgroundElements::drawStars(Engine::SpriteBatch& spriteBatch)
{
	for (int i = 0; i < m_starPosition.size(); i++)
	{
		glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

		glm::vec4 posAndDim(m_starPosition[i].x, m_starPosition[i].y, m_stars[0].width, m_stars[0].height);

		spriteBatch.draw(posAndDim, uv, m_starID[i], 0.0f, m_color);

	}
}