#include "GameManager.h"
#include <filesystem>

using namespace std;

const std::string LEVELS_PATH = "data/levels";

GameManager::GameManager() : m_levelList(getLevelList(LEVELS_PATH)), m_activeGame(nullptr)
{
}

std::vector<std::string> GameManager::getLevelList(std::string levelsPath)
{
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(levelsPath))
        if (entry.path().extension() == ".json")
            files.push_back(entry.path().string());
    return files;
}

void GameManager::runLevel(std::string levelPath)
{
	if (!m_activeGame)
	{
		m_activeGame = new Game(levelPath);
		m_activeGame->run();
	}
}
