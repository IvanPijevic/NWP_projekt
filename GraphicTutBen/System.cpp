#include "System.h"

System::System() :
	m_screenWidth(1024),
	m_screenHeight(768),
	m_gameState(GameState::MAIN_MENU),
	m_time(0.0f),
	m_maxFPS(60.0f),
	m_player(nullptr),
	m_startPos(glm::vec2(0, 500)),
	m_currentWave(0),
	m_screenSize(0)
{
	m_camera.init(m_screenWidth, m_screenHeight);
	m_hudCamera.init(m_screenWidth, m_screenHeight);
	m_hudCamera.setPosition(glm::vec2(m_screenWidth / 2, m_screenHeight / 2));
}

System::~System()
{
	delete m_player;
}

void System::Run()
{
	InitSystem();

	GameLoop();
}

void System::InitSystem()
{
	Engine::init();
	m_window.create("Game Engine", m_screenWidth, m_screenHeight, m_screenSize);

	InitShaders();

	m_spriteBatch.init();
	m_uiSpriteBatch.init();

	//Initialize sprite font
	m_spriteFont = new Engine::SpriteFont("Textures/Font/kenvector_future_thin.ttf", 32);

	m_fpsLimiter.init(m_maxFPS);

	//Init main menu
	m_userInterface = new UserInterface();
	m_userInterface->initMainMenu(m_screenWidth, m_screenHeight);

	//Init numbers
	m_userInterface->initNumbers();

	//Init background
	m_background = new Background();
	m_background->init(m_spriteBatch, m_screenWidth, m_screenHeight);

	//Init background elements
	m_backgroundElements = new BackgroundElements();
	m_backgroundElements->init();

	//Init enemy/level setup
	m_enemy.initEnemyWaves(m_levelData);

	//Init player
	m_player = new Player();
	m_player->init(5.0f, 100, 3, glm::vec2(0.0f, -300.0f), &m_inputManager, &m_bullets);

	//Init weapons
	m_player->addWeapon(new Weapon("Basic gun", 10, 1, 5, 20));
	m_player->addWeapon(new Weapon("Double laser", 10, 2, 5, 20));
}

void System::InitShaders()
{
	m_colorProgram.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_colorProgram.AddAttribute("vertexPosition");
	m_colorProgram.AddAttribute("vertexColor");
	m_colorProgram.AddAttribute("vertexUV");
	m_colorProgram.LinkShaders();
}

void System::GameLoop()
{
	const float DESIRED_FPS = 60.0f;
	const int MAX_PHYSICS_STEPS = 6;
	const float MS_PER_SECOND = 1000;
	const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;
	const float MAX_DELTA_TIME = 1.0f;

	float previousTicks = SDL_GetTicks();

	while (m_gameState != GameState::EXIT)
	{
		m_fpsLimiter.begin();

		Input();
		
		m_inputManager.update();

		m_time += 0.01;

		m_camera.update();
		m_hudCamera.update();

		if (m_gameState == GameState::PLAY)
		{
			float newTicks = SDL_GetTicks();
			float frameTime = newTicks - previousTicks;
			previousTicks = newTicks;
			float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

			int i = 0;
			while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS)
			{
				float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);

				updateAgents(deltaTime);
				updateBullets(deltaTime);
				
				m_backgroundElements->updateBackground(deltaTime, m_screenHeight);
				m_backgroundElements->randomStarTexture();
				m_backgroundElements->pickStarPosition(m_screenWidth, m_screenHeight);

				totalDeltaTime -= deltaTime;
				i++;
			}

			//Print once every 10 frames
			static int frameCounter = 0;
			frameCounter++;
			if (frameCounter == 10)
			{
				std::cout << m_fps << std::endl;
				frameCounter = 0;
			}
		}

		if (m_gameState == GameState::OPTIONS)
		{

		}

		DrawGame();

		m_fps = m_fpsLimiter.end();
	}
}

void System::Input()
{
	SDL_Event evnt;

	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;

		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			m_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;

		case SDL_KEYDOWN:
			m_inputManager.pressKey(evnt.key.keysym.sym);
			break;

		case SDL_KEYUP:
			m_inputManager.releaseKey(evnt.key.keysym.sym);
			break;

		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(evnt.button.button);
			break;

		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(evnt.button.button);
			break;
		}
	}

	if (m_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouseCoords = m_inputManager.getMouseCoords();
		mouseCoords = m_camera.convertScreenToWorld(mouseCoords);
		mouseCoords.y *= (-1);
		std::cout << mouseCoords.x << " and " << mouseCoords.y << std::endl;
		
		if (m_userInterface->clickedOnPlayButton(mouseCoords))
		{
			m_gameState = GameState::PLAY;
		}

		if (m_userInterface->clickedOnOptionsButton(mouseCoords))
		{
			m_gameState = GameState::OPTIONS;
		}

		if (m_userInterface->clickedOnQuitButton(mouseCoords))
		{
			m_gameState = GameState::EXIT;
		}
	}

	//Enter / Exit main menu
	if (m_inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		if (m_gameState == GameState::PLAY)
		{
			m_gameState = GameState::MAIN_MENU;
		}
		else
		{
			m_gameState = GameState::PLAY;
		}
	}
}

void System::DrawGame()
{
	//Set the base depth to 1.0
	glClearDepth(1.0);
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Enable shader
	m_colorProgram.Use();

	//Using texture unit 0
	glActiveTexture(GL_TEXTURE0);
	//Get the uniform location
	GLint textureLocation = m_colorProgram.getUniformLocation("mySampler");
	//Tell the shader that the texture is in texture unit 0
	glUniform1i(textureLocation, 0);

	//Set the camera matrix
	GLint pLocation = m_colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	
	m_spriteBatch.begin();

	switch (m_gameState)
	{
	case GameState::MAIN_MENU:
		glm::vec2 mouseCoords = m_inputManager.getMouseCoords();
		mouseCoords = m_camera.convertScreenToWorld(mouseCoords);
		mouseCoords.y *= (-1);

		//Draw buttons
		m_userInterface->drawPlayButton(m_spriteBatch, mouseCoords);
		m_userInterface->drawOptionsButton(m_spriteBatch, mouseCoords);
		m_userInterface->drawQuitButton(m_spriteBatch, mouseCoords);

		break;

	case GameState::OPTIONS:

		break;

	case GameState::PLAY:

		
		//Draw background
		m_background->coverBackground(m_screenWidth, m_screenHeight, m_spriteBatch);
		
		//Draw background elements(stars/comets/planets...)
		m_backgroundElements->drawStars(m_spriteBatch);

		//Draw player
		m_player->draw(m_spriteBatch);

		//Draw enemy
		for (int i = 0; i < m_enemyVec.size(); i++)
		{
			//Check is enemy on screen
			if (m_camera.isBoxInView(m_enemyVec[i]->getPosition(), m_enemyVec[i]->getDimension()))
			{
				m_enemyVec[i]->draw(m_spriteBatch);
			}
		}

		//Draw effects
		for (int i = 0; i < m_player->getEffectVec().size(); i++)
		{
			//Check isi effect on screen
			if (m_camera.isBoxInView(m_player->getEffectVec()[i]->getPosition(), m_player->getEffectVec()[i]->getDimension()))
			{
				m_player->getEffectVec()[i]->draw(m_spriteBatch);
			}
		}

		//Draw bullets
		for (int i = 0; i < m_bullets.size(); i++)
		{
				m_bullets[i].draw(m_spriteBatch);
		}

		break;
	}

	m_spriteBatch.end();

	m_spriteBatch.renderBatch();

	if (m_gameState == GameState::PLAY)
	{
		//Render the heads up display
		DrawHud();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	m_colorProgram.Unuse();

	//Swap our buffer and draw everything to the screen
	m_window.swapBuffer();
}

void System::updateBullets(float deltaTime)
{
	// Update colision Bullets -> Enemy
	for (int i = m_enemyVec.size() - 1; i >= 0; --i)
	{
		for (int j = m_bullets.size() - 1; j >= 0; --j)
		{
			if (m_bullets[j].colideWithAgent(*m_enemyVec[i]))
			{
				// Reduce health points
				m_enemyVec[i]->setHealthPoints(m_enemyVec[i]->getHealthPoints() - m_bullets[j].getDamage());
				// Delete bullet
				m_bullets[j] = std::move(m_bullets.back());
				m_bullets.pop_back();
				--j;
				if (m_enemyVec[i]->getHealthPoints() <= 0)
				{
					// Update destroyed ships
					m_enemy.setShipsDestroyed(m_enemy.getShipsDestroyed() + 1);
					// Delete enemy ship from vector
					m_enemyVec[i] = std::move(m_enemyVec.back());
					m_enemyVec.pop_back();
					--i; 
					break;
				}
			}
		}
	}
	// Update bullets (movement, lifeTime)
	for (int i = m_bullets.size() - 1; i >= 0; --i)
	{
		m_bullets[i].update(m_screenHeight, deltaTime);
		if (m_bullets[i].getLifeTime() <= 0)
		{
			m_bullets[i] = std::move(m_bullets.back());
			m_bullets.pop_back();
		}
	}
}

void System::updateAgents(float deltaTime)
{
	//Update Player
	m_player->update(m_inputManager, m_screenWidth, m_screenHeight, deltaTime);

	//Add enemy to vector (initialize wave)
	if (m_enemy.getIsWaveDead())
	{
		m_enemy.addEnemyToVector(m_enemyVec, m_levelData, m_currentWave, m_startPos, m_screenWidth, m_screenHeight);
	}

	if (m_enemyVec.size() == 0)
	{
		m_currentWave++;
		if (m_currentWave >= m_levelData.size())
		{
			Engine::fatalError("Game over!");
			m_gameState = GameState::EXIT;
		}
		m_enemy.setIsWaveDead(true);
	}

	//Update colision Player->Enemy
	for (int i = 0; i < m_enemyVec.size(); i++)
	{
		if (m_player->colideWithEnemy(m_enemyVec[i]))
		{
			//Reduce number of lives
			m_player->setPlayerLives(m_player->getPlayerLives() - 1);

			//Check is lives > 0
			if (m_player->getPlayerLives() <= 0)
			{
				m_gameState = GameState::EXIT;
			}

			//Restart player position after HP reach zero
			m_player->setPlayerPosition(m_player->getPlayerStartPosition());
		}
	}

	//Check is enemy on screen
	m_enemy.isEnemyOnScreen(m_screenWidth, m_screenHeight, m_enemyVec);

	//Update enemy (movement)
	for (int i = 0; i < m_enemyVec.size(); i++)
	{
		m_enemyVec[i]->update(m_screenWidth, m_screenHeight, m_levelData, m_currentWave, deltaTime);
	}
}

void System::DrawHud()
{
	char scoreBuffer[256];
	char playerHPBuffer[256];

	//Set the HUD Camera matrix
	GLint pLocation = m_colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_hudCamera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_uiSpriteBatch.begin();

	//Score
	sprintf_s(scoreBuffer, "Score: %d", m_enemy.getShipsDestroyed());
	m_spriteFont->draw(m_uiSpriteBatch, scoreBuffer, glm::vec2(0, 0),
		glm::vec2(1.0), 0.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	//PlayerHP
	sprintf_s(playerHPBuffer, "HP: %d", m_player->getHP());
	m_spriteFont->draw(m_uiSpriteBatch, playerHPBuffer, glm::vec2(0, 40.0f),
		glm::vec2(1.0), 0.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_uiSpriteBatch.end();
	m_uiSpriteBatch.renderBatch();
}