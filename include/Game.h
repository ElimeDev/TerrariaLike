#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "TileMap.h"
#include "Player.h"
#include "Input.h"

class Game
{
public:
	Game(std::string levelPath);
	~Game();
	
	void run();

private:
	sf::RenderWindow m_window;
	Input m_input;

	sf::Clock m_clock; //pr calculer delta time
	float m_deltaTime;

	TileMap m_tilemap;
	Player m_player;
};

