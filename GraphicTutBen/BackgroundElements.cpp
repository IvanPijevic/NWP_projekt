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
	std::vector<glm::vec2>::iterator newEnd = std::remove_if(m_starPosition.begin(),m_starPosition.end(),[&](glm::vec2& pos)
		{
			bool offscreen = pos.y < (-screenHeight / 2);
			if (offscreen) 
			{
				size_t i = &pos - &m_starPosition[0];
				m_starID[i] = m_starID.back();
				m_starID.pop_back();
			}

			else
			{
				pos.y -= m_starSpeed * deltaTime;
			}
			return offscreen;
		});

	m_starPosition.erase(newEnd, m_starPosition.end());

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
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	std::for_each(m_starPosition.begin(), m_starPosition.end(), [&](const glm::vec2& pos) 
		{
			size_t i = &pos - &m_starPosition[0];
			glm::vec4 posAndDim(pos.x, pos.y, m_stars[0].width, m_stars[0].height);
			spriteBatch.draw(posAndDim, uv, m_starID[i], 0.0f, m_color);});
}