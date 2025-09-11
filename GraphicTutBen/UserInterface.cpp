#include "UserInterface.h"

void UserInterface::initMainMenu(int screenWidth, int screenHeight)
{
	for (int i = 1; i < 31; i++)
	{
		std::ostringstream oss;
		oss << "Textures/PNG/UI/button/Play/Play button 300x80 hover" << std::setw(6) << std::setfill('0') << i << ".png";
		m_texture = Engine::ResourceManager::getTexture(oss.str());
		m_playButton.push_back(m_texture);
	}

	for (int i = 1; i < 31; i++)
	{
		std::ostringstream oss;
		oss << "Textures/PNG/UI/button/Quit/Quit button 300x80 hover" << std::setw(6) << std::setfill('0') << i << ".png";
		m_texture = Engine::ResourceManager::getTexture(oss.str());
		m_quitButton.push_back(m_texture);
	}

	m_buttonTextureWidth = m_texture.width;
	m_buttonTextureHeight = m_texture.height;

	m_playButtonPosition.x = -(m_buttonTextureWidth / 2);
	m_playButtonPosition.y = m_buttonTextureHeight;

	m_quitButtonPosition.x = -(m_buttonTextureWidth / 2);
	m_quitButtonPosition.y = - 2 * m_buttonTextureHeight;

	m_uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	m_color = Engine::ColorRGBA8(255, 255, 255, 255);
}

void UserInterface::initNumbers()
{
	for (int i = 0; i < 10; i++)
	{
		m_texture = Engine::ResourceManager::getTexture("Textures/PNG/UI/numeral" + std::to_string(i) + ".png");
		m_numbers.push_back(m_texture);
	}
}

void UserInterface::drawPlayButton(Engine::SpriteBatch& spriteBatch, glm::vec2 mouseCoord)
{
	glm::vec4 posAndSize = glm::vec4(m_playButtonPosition.x, m_playButtonPosition.y, m_buttonTextureWidth, m_buttonTextureHeight);

	if (mouseCoord.x > m_playButtonPosition.x && mouseCoord.x < m_playButtonPosition.x + m_playButton[0].width
		&& mouseCoord.y > m_playButtonPosition.y && mouseCoord.y < m_playButtonPosition.y + m_playButton[0].height)
	{
		spriteBatch.draw(posAndSize, m_uv, m_playButton[m_vectorCounter].id, 0.0f, m_color);

		//Animate button
		animateButton();

		//Reset vector counter when reach end of vector
		if (m_vectorCounter == m_playButton.size())
		{
			m_vectorCounter = 0;
		}
	}
	else
	{
		//Draw static button
		spriteBatch.draw(posAndSize, m_uv, m_playButton[0].id, 0.0f, m_color);
	}
}

void UserInterface::drawQuitButton(Engine::SpriteBatch& spriteBatch, glm::vec2 mouseCoord)
{
	glm::vec4 posAndSize = glm::vec4(m_quitButtonPosition.x, m_quitButtonPosition.y, m_buttonTextureWidth, m_buttonTextureHeight);

	if (mouseCoord.x > m_quitButtonPosition.x && mouseCoord.x < m_quitButtonPosition.x + m_quitButton[0].width
		&& mouseCoord.y > m_quitButtonPosition.y && mouseCoord.y < m_quitButtonPosition.y + m_quitButton[0].height)
	{
		spriteBatch.draw(posAndSize, m_uv, m_quitButton[m_vectorCounter].id, 0.0f, m_color);

		//Animate button
		animateButton();

		//Reset vector counter when reach end of vector
		if (m_vectorCounter == m_quitButton.size())
		{
			m_vectorCounter = 0;
		}
	}
	else
	{
		//Draw static button
		spriteBatch.draw(posAndSize, m_uv, m_quitButton[0].id, 0.0f, m_color);
	}
}

void UserInterface::animateButton()
{
	//Animate button
	if (m_drawCounter >= m_drawSpeed)
	{
		m_vectorCounter++;
		m_drawCounter = 0;
	}

	m_drawCounter++;
}

bool UserInterface::clickedOnPlayButton(glm::vec2 mouseCoord)
{
	return mouseCoord.x > m_playButtonPosition.x && mouseCoord.x < m_playButtonPosition.x + m_playButton[0].width
		&& mouseCoord.y > m_playButtonPosition.y && mouseCoord.y < m_playButtonPosition.y + m_playButton[0].height;
}

bool UserInterface::clickedOnQuitButton(glm::vec2 mouseCoord)
{
	return mouseCoord.x > m_quitButtonPosition.x && mouseCoord.x < m_quitButtonPosition.x + m_playButton[0].width
		&& mouseCoord.y > m_quitButtonPosition.y && mouseCoord.y < m_quitButtonPosition.y + m_playButton[0].height;
}