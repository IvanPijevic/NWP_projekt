#ifndef SYSTEM_H
#define SYSTEM_H

#include <Windows.h>
#include <iostream>

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <algorithm>

#include <Engine/Engine.h>
#include <Engine/Window.h>
#include <Engine/Camera2D.h>
#include <Engine/Error.h>
#include <Engine/GLSL.h>
#include <Engine/Texture.h>
#include <Engine/SpriteBatch.h>
#include <Engine/ResourceManager.h>
#include <Engine/InputManager.h>
#include <Engine/Timing.h>
#include <Engine/SpriteFont.h>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Background.h"
#include "UserInterface.h"
#include "BackgroundElements.h"

enum class GameState {MAIN_MENU, PLAY, EXIT};

class System
{
public:
	System();

	void Run();

private:
	void InitSystem();
	void InitShaders();
	void GameLoop();
	void Input();
	void DrawGame();
	void DrawHud();

	void updateBullets(float deltaTime);
	void updateAgents(float deltaTime);


	Engine::Window m_window;
	Engine::GLSL m_colorProgram;
	Engine::Camera2D m_camera;
	Engine::Camera2D m_hudCamera;
	Engine::InputManager m_inputManager;
	Engine::FpsLimiter m_fpsLimiter;
	Engine::SpriteBatch m_spriteBatch;
	Engine::SpriteBatch m_uiSpriteBatch;
	Engine::SpriteFont* m_spriteFont;
	
	Player m_player;
	Enemy m_enemy;
	Background m_background;
	UserInterface m_userInterface;
	BackgroundElements m_backgroundElements;

	std::vector<Bullet> m_bullets;
	std::vector<Enemy*>  m_enemyVec;
	std::vector<LevelData> m_levelData;

	glm::vec2 m_position;
	glm::vec2 m_startPos;

	int m_screenWidth;
	int m_screenHeight;
	int m_currentWave;
	int m_screenSize;

	GameState m_gameState;

	float m_maxFPS;
	float m_fps;
	float m_time;

};

#endif