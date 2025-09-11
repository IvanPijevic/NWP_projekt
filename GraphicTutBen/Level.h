#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <fstream>

#include <Engine/Error.h>

class Level
{
public:
	void init(const std::string& fileName);

	int getNumberOfWaves() const { return m_numberOfWaves; }
	int getNumberOfBosses() const { return m_numberOfBosses; }

	const std::vector<std::string>& getLevelData() const { return m_levelData; }

private:
	std::vector<std::string> m_levelData;

	int m_numberOfWaves;
	int m_numberOfBosses;
	int m_numberOfEnemyShipsInWave;
	std::string m_enemyType;
};

#endif