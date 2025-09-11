#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <Engine/InputManager.h>
#include <Engine/SpriteBatch.h>
#include <Engine/ResourceManager.h>
#include <Engine/Camera2D.h>

#include <string>
#include <format>
#include <iomanip>
#include <sstream>

enum class buttonType
{
	PLAY, EXIT
};

class UserInterface
{
public:
	void initMainMenu(int screenWidth, int screenHeight);
	void initNumbers();

	void drawPlayButton(Engine::SpriteBatch& spriteBatch, glm::vec2 mouseCoord);
	void drawQuitButton(Engine::SpriteBatch& spriteBatch, glm::vec2 mouseCoord);

	void animateButton();

	bool clickedOnPlayButton(glm::vec2 mouseCoord);
	bool clickedOnQuitButton(glm::vec2 mouseCoord);

private:
	Engine::Texture m_texture;
	Engine::Camera2D m_camera;
	Engine::ColorRGBA8 m_color;

	int m_drawSpeed = 3;
	int m_drawCounter = 0;
	int m_vectorCounter = 0;
	int m_numberOfButtons = 2;
	int m_buttonTextureWidth;
	int m_buttonTextureHeight;

	glm::vec2 m_playButtonPosition;
	glm::vec2 m_quitButtonPosition;

	glm::vec4 m_uv;

	std::vector<Engine::Texture> m_playButton;
	std::vector<Engine::Texture> m_quitButton;
	std::vector<Engine::Texture> m_numbers;
};

#endif