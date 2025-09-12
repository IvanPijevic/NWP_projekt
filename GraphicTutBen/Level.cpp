#include "Level.h"

void Level::init(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open()) {
        Engine::fatalError("Fail to open " + fileName);
    }

    m_levelData.reserve(1000);
    std::string temp;
    while (std::getline(file, temp)) {
        m_levelData.push_back(std::move(temp));
    }

    m_numberOfWaves = m_levelData.size();
}