#ifndef ENEMY_H
#define ENEMY_H

#include <Engine/SpriteBatch.h>
#include <Engine/ResourceManager.h>

#include <vector>
#include <memory>
#include <sstream>
#include <string>

#include "Agent.h"
#include "Level.h"

enum class TRAJECTORY
{
	WAVE_LIKE, SPIRAL, VERTICAL, DIAGONAL
};

enum class ENEMY_TYPE
{
	DRONE, GUN_SHIP, BATTLE_SHIP, DESTROYER
};

struct LevelData
{
	int numberOfShips = 0;
	ENEMY_TYPE enemyType;
	TRAJECTORY trajectory;
};

class Enemy : public Agent
{
public:
	Enemy();

	void initEnemy(glm::vec2 position, std::vector<LevelData>& data, int currentWave);
	void draw(Engine::SpriteBatch& spriteBatch);
	void update(int screenWidth, int screenHeight, std::vector<LevelData>& data, int currentWave, float deltaTime);

	void initEnemyWaves(std::vector<LevelData>& data);
	void addEnemyToVector(std::vector<std::unique_ptr<Enemy>>& enemy, std::vector<LevelData>& waveData, int currentWave, glm::vec2& position, int screenWidth, int screenHeight);
	void isEnemyOnScreen(int screenWidth, int screenHeight, std::vector<std::unique_ptr<Enemy>>& enemy);

	bool getIsWaveDead() const { return m_isWaveDead; }
	int getHealthPoints() const  { return m_healthPoints; }
	int getShipsDestroyed() const { return m_shipsDestroyed; }

	
	void setIsWaveDead(bool isDead) { m_isWaveDead = isDead; }
	void setHealthPoints(int HP) { m_healthPoints = HP; }
	void setShipsDestroyed(int shipsDestroyed) { m_shipsDestroyed = shipsDestroyed; }

private:
	int m_numberOfWaves = 0;
	int m_shipsDestroyed = 0;

	Engine::ColorRGBA8 m_color;

	bool m_isWaveDead = true;

	Level m_level;
};

#endif