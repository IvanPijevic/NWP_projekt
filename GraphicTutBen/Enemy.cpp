#include "Enemy.h"

Enemy::Enemy()
{
	m_level.init("Levels/LevelOne.txt");
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
	std::vector<std::string> levelData = m_level.getLevelData();
	data.clear();

	for (int i = 0; i < levelData.size(); ++i) 
	{
		std::stringstream ss(levelData[i]);
		std::string key;
		ss >> key;

		if (i % 3 == 0) 
		{
			data.push_back(LevelData());

			int number;
			ss >> number;
			if (ss.fail()) 
			{
				data.back().numberOfShips = 0;
			}
			else 
			{
				data.back().numberOfShips = number;
			}
		}
		else if (i % 3 == 1) 
		{
			std::string type;
			ss >> type;

			if (type == "DRONE")
				data.back().enemyType = ENEMY_TYPE::DRONE;
			else if (type == "GUN_SHIP")
				data.back().enemyType = ENEMY_TYPE::GUN_SHIP;
			else if (type == "BATTLE_SHIP")
				data.back().enemyType = ENEMY_TYPE::BATTLE_SHIP;
			else if (type == "DESTROYER")
				data.back().enemyType = ENEMY_TYPE::DESTROYER;
		}
		else if (i % 3 == 2) 
		{
			std::string put;
			ss >> put;

			if (put == "WAVE_LIKE")
				data.back().trajectory = TRAJECTORY::WAVE_LIKE;
			else if (put == "VERTICAL")
				data.back().trajectory = TRAJECTORY::VERTICAL;
		}
	}
}

void Enemy::addEnemyToVector(std::vector<std::unique_ptr<Enemy>>& enemy, std::vector<LevelData>& waveData, int currentWave, glm::vec2& position, int screenWidth, int screenHeight)
{
	float shipInterspace = 120.0f;

	if (waveData[currentWave].trajectory == TRAJECTORY::VERTICAL)
	{
		position.x = -((waveData[currentWave].numberOfShips - 1) * shipInterspace + 50.0f) / 2;
	}

	for (int i = 0; i < waveData[currentWave].numberOfShips; i++)
	{
		std::unique_ptr<Enemy> e = std::make_unique<Enemy>();
		e->initEnemy(position, waveData, currentWave);
		enemy.push_back(std::move(e));

		if (waveData[currentWave].trajectory == TRAJECTORY::VERTICAL)
		{
			position.x += shipInterspace;
		}

		if (waveData[currentWave].trajectory == TRAJECTORY::WAVE_LIKE)
		{
			position.y += enemy.back()->getWidth();
		}
	}

	m_isWaveDead = false;
}

void Enemy::isEnemyOnScreen(int screenWidth, int screenHeight, std::vector<std::unique_ptr<Enemy>>& enemy)
{
	enemy.erase(std::remove_if(enemy.begin(), enemy.end(),[screenHeight](const std::unique_ptr<Enemy>& e) 
		{
				return e->m_position.y < -(screenHeight / 2 + e->m_texture.height);
		}), enemy.end());
}