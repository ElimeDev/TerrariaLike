#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.h"

class Game
{
public:
	Game();
	~Game();
	
	void run();

private:
	sf::RenderWindow m_window;
};

