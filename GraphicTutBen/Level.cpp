#include "Level.h"

void Level::init(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);

	if (file.fail())
	{
		Engine::fatalError("Fail to open " + fileName);
	}

	std::string temp;

	while (std::getline(file, temp))
	{
		m_levelData.push_back(temp);
	}
}