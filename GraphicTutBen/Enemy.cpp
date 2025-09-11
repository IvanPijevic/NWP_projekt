#include "Enemy.h"

Enemy::Enemy()
{
	m_level = std::make_unique<Level>();
	m_level->init("Levels/LevelOne.txt");
}

void Enemy::initEnemy(glm::vec2 position, std::vector<LevelData>& data, int currentWave)
{
	m_position = position;
	m_color = Engine::ColorRGBA8(255, 255, 255, 255);

	switch (data[currentWave].enemyType)
	{
	case ENEMY_TYPE::DRONE:
		m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Enemies/enemyBlack1.png");
		m_healthPoints = 20;
		m_shieldPoints = 0;
		break;

	case ENEMY_TYPE::GUN_SHIP:
		m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Enemies/enemyBlack2.png");
		m_healthPoints = 30;
		m_shieldPoints = 0;
		break;

	case ENEMY_TYPE::BATTLE_SHIP:
		m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Enemies/enemyBlack3.png");
		m_healthPoints = 40;
		m_shieldPoints = 0;
		break;

	case ENEMY_TYPE::DESTROYER:
		m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Enemies/enemyBlack4.png");
		m_healthPoints = 50;
		m_shieldPoints = 0;
		break;
		
	default:

		break;
	}
	
}

void Enemy::draw(Engine::SpriteBatch& spriteBatch)
{
	glm::vec4 posAndSize = glm::vec4(m_position.x, m_position.y, m_texture.width, m_texture.height);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	spriteBatch.draw(posAndSize, uv, m_texture.id, 0.0f, m_color);
}

void Enemy::update(int screenWidth, int screenHeight, std::vector<LevelData>& data, int currentWave, float deltaTime)
{
	switch (data[currentWave].trajectory)
	{
	case TRAJECTORY::WAVE_LIKE:
		m_position.x = cos(m_position.y * 0.02) * (screenWidth / 3);
		m_position.y--;
		break;

	case TRAJECTORY::VERTICAL:
		m_position.y--;
		break;

	default:

		break;
	}
}

void Enemy::initEnemyWaves(std::vector<LevelData>& data)
{
	std::vector<std::string> levelData = m_level->getLevelData();
	int vecCounter = 0;
	data.push_back(LevelData());

	for (int i = 0; i < levelData.size(); i++)
	{
		if (i % 3 == 0 && i > 0)
		{
			vecCounter++;
			data.push_back(LevelData());
		}

		std::stringstream ss(levelData[i]);
		std::string tempInfo;
		ss >> tempInfo;

		if (!(ss >> tempInfo))
		{
			continue;
		}

		// Get number of ships in wave
		if (i % 3 == 0)
		{
			try
			{
				data[vecCounter].numberOfShips = std::stoi(tempInfo);
			}
			catch (const std::invalid_argument&)
			{
				data[vecCounter].numberOfShips = 0;
			}
		}

		// Get type of enemy ships
		else if (i % 3 == 1)
		{
			if (tempInfo == "DRONE")
				data[vecCounter].enemyType = ENEMY_TYPE::DRONE;
			else if (tempInfo == "GUN_SHIP")
				data[vecCounter].enemyType = ENEMY_TYPE::GUN_SHIP;
			else if (tempInfo == "BATTLE_SHIP")
				data[vecCounter].enemyType = ENEMY_TYPE::BATTLE_SHIP;
			else if (tempInfo == "DESTROYER")
				data[vecCounter].enemyType = ENEMY_TYPE::DESTROYER;
		}

		// Get enemy trajectory
		else if (i % 3 == 2)
		{
			if (tempInfo == "WAVE_LIKE")
				data[vecCounter].trajectory = TRAJECTORY::WAVE_LIKE;
			else if (tempInfo == "VERTICAL")
				data[vecCounter].trajectory = TRAJECTORY::VERTICAL;
		}
	}
}

void Enemy::addEnemyToVector(std::vector<Enemy*>& enemy, std::vector<LevelData>& waveData, int currentWave, glm::vec2& position, int screenWidth, int screenHeight)
{
	float shipInterspace = 120.0f;

	if (waveData[currentWave].trajectory == TRAJECTORY::VERTICAL)
	{
		position.x = -((waveData[currentWave].numberOfShips - 1) * shipInterspace + 50.0f) / 2;
	}

	for (int i = 0; i < waveData[currentWave].numberOfShips; i++)
	{
		enemy.push_back(new Enemy);
		enemy.back()->initEnemy(position, waveData, currentWave);

		if (waveData[currentWave].trajectory == TRAJECTORY::VERTICAL)
		{
			position.x += shipInterspace;
		}

		if (waveData[currentWave].trajectory == TRAJECTORY::WAVE_LIKE)
		{
			position.y += enemy[i]->getWidth();
		}
	}

	m_isWaveDead = false;
}

void Enemy::isEnemyOnScreen(int screenWidth, int screenHeight, std::vector<Enemy*>& enemy)
{
	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy[i]->m_position.y < -(screenHeight / 2 + enemy[i]->m_texture.height))
		{
			delete enemy[i];
			enemy[i] = enemy.back();
			enemy.pop_back();
		}
	}
}