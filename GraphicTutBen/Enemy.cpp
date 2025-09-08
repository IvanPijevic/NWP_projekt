#include "Enemy.h"

Enemy::Enemy() :
	m_numberOfWaves(0),
	m_isWaveDead(true)
{
	m_level = new Level;
	m_level->init("Levels/LevelOne.txt");
}

Enemy::~Enemy()
{}

void Enemy::initEnemy(glm::vec2 position, std::vector<LevelData>& data, int currentWave)
{
	m_position = position;
	m_color = Engine::ColorRGBA8(255, 255, 255, 255);

	switch (data[currentWave].enemyType)
	{
	case ENEMY_TYPE::DRONE:
		m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Enemies/enemyBlack1.png");
		m_healthPoints = 10;
		m_shieldPoints = 0;
		break;

	case ENEMY_TYPE::GUN_SHIP:
		m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Enemies/enemyBlack2.png");
		m_healthPoints = 20;
		m_shieldPoints = 0;
		break;

	case ENEMY_TYPE::BATTLE_SHIP:
		m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Enemies/enemyBlack3.png");
		m_healthPoints = 30;
		m_shieldPoints = 10;
		break;

	case ENEMY_TYPE::DESTROYER:
		m_texture = Engine::ResourceManager::getTexture("Textures/PNG/Enemies/enemyBlack4.png");
		m_healthPoints = 30;
		m_shieldPoints = 30;
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
	case TRAJECTORY::COS:
		m_position.x = cos(m_position.y * 0.02) * (screenWidth / 3);
		m_position.y-- * deltaTime;
		break;

	case TRAJECTORY::VERTICAL:
		m_position.y-- * deltaTime;
		break;

	default:

		break;
	}
}

void Enemy::initEnemyWaves(std::vector<LevelData>& data)
{
	std::vector<std::string> levelData = m_level->getLevelData();

	std::string temp;
	int lineCounter = 0;
	int vecCounter = 0;

	data.push_back(LevelData());

	for (int i = 0; i < levelData.size(); i++)
	{
		bool usefulInfo = false;
		std::string tempInfo = "";

		temp = levelData[i];

		if (i % 3 == 0 && i > 0)
		{
			lineCounter = 0;
			vecCounter++;
			data.push_back(LevelData());
		}

		for (char& c : temp)
		{
			if (usefulInfo)
			{
				tempInfo += c;
			}

			if (c == ' ')
			{
				usefulInfo = true;
			}
		}

		//Get number of ships in wave
		if (lineCounter == 0 && usefulInfo)
		{
			data[vecCounter].numberOfShips = std::stoi(tempInfo);
		}

		//Get type of enemy ships
		if (lineCounter == 1 && usefulInfo)
		{
			if (tempInfo == "DRONE")
			{
				data[vecCounter].enemyType = ENEMY_TYPE::DRONE;
			}

			if (tempInfo == "GUN_SHIP")
			{
				data[vecCounter].enemyType = ENEMY_TYPE::GUN_SHIP;
			}

			if (tempInfo == "BATTLE_SHIP")
			{
				data[vecCounter].enemyType = ENEMY_TYPE::BATTLE_SHIP;
			}

			if (tempInfo == "DESTROYER")
			{
				data[vecCounter].enemyType = ENEMY_TYPE::DESTROYER;
			}
		}

		//Get enemy trajectory
		if (lineCounter == 2 && usefulInfo)
		{
			if (tempInfo == "COS")
			{
				data[vecCounter].trajectory = TRAJECTORY::COS;
			}

			if (tempInfo == "VERTICAL")
			{
				data[vecCounter].trajectory = TRAJECTORY::VERTICAL;
			}
		}

		lineCounter++;
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

		if (waveData[currentWave].trajectory == TRAJECTORY::COS)
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