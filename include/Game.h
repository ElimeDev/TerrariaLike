#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();
	
	void run();

private:
	sf::RenderWindow m_window;
	TileMap m_tilemap;
	Player m_player;
};

