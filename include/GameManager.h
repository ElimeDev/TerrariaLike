#pragma once

#include <vector>
#include <string>
#include "Game.h"

class GameManager
{
public:
	GameManager();

private:
	std::vector<std::string> getLevelList(std::string levelsPath); //renvois la liste des chemins vers les niveaux

	void runLevel(std::string levelPath); //lance un niveau à partir de son chemin

	std::vector<std::string> m_levelList; //liste des chemins vers les niveaux
	Game *m_activeGame; //instance active du jeu
};

