#include "Level.h"

Level::Level()
{}

Level::~Level()
{}

void Level::init(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);

	if (file.fail())
	{
		Engine::fatalError("Fail to open " + fileName);
	}

	std::string temp;

	//file >> temp >> m_numberOfWaves;
	//std::getline(file, temp); 

	while (std::getline(file, temp))
	{
		m_levelData.push_back(temp);
	}
}