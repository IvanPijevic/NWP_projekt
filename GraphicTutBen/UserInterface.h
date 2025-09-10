#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <Engine/InputManager.h>
#include <Engine/SpriteBatch.h>
#include <Engine/ResourceManager.h>
#include <Engine/Camera2D.h>

#include <string>

enum class buttonType
{
	PLAY, OPTIONS, EXIT
};

class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void initMainMenu(int screenWidth, int screenHeight);
	void initNumbers();

	void drawPlayButton(Engine::SpriteBatch& spriteBatch, glm::vec2 mouseCoord);
	void drawOptionsButton(Engine::SpriteBatch& spriteBatch, glm::vec2 mouseCoord);
	void drawQuitButton(Engine::SpriteBatch& spriteBatch, glm::vec2 mouseCoord);

	void animateButton();

	bool clickedOnPlayButton(glm::vec2 mouseCoord);
	bool clickedOnOptionsButton(glm::vec2 mouseCoord);
	bool clickedOnQuitButton(glm::vec2 mouseCoord);

private:
	Engine::Texture m_texture;
	Engine::Camera2D m_camera;
	Engine::ColorRGBA8 m_color;

	int m_drawSpeed;
	int m_drawCounter;
	int m_vectorCounter;
	int m_numberOfButtons;
	int m_buttonTextureWidth;
	int m_buttonTextureHeight;

	glm::vec2 m_playButtonPosition;
	glm::vec2 m_optionsButtonPosition;
	glm::vec2 m_quitButtonPosition;

	glm::vec4 m_uv;

	std::vector<Engine::Texture> m_playButton;
	std::vector<Engine::Texture> m_optionsButton;
	std::vector<Engine::Texture> m_quitButton;
	std::vector<Engine::Texture> m_numbers;
};

#endif