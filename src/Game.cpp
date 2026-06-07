#include "Game.h"

using namespace sf;

const std::string TILEMAP_FILEPATH = "data/TileMap.json";
const std::string PLAYER_DATA_FILEPATH = "data/PlayerData.json";

Game::Game(std::string levelPath) : m_window(sf::VideoMode(810, 612), "TerrariaLike", sf::Style::Titlebar | sf::Style::Close), m_deltaTime(0.f)
{
	m_tilemap.load(TILEMAP_FILEPATH);
	m_player.load(PLAYER_DATA_FILEPATH);
}

Game::~Game()
{
}

void Game::run()
{
	while (m_window.isOpen())
	{
		Event event;
		while (m_window.pollEvent(event))
		{
			m_input.InputHandler(event, m_window);
		}

		m_deltaTime = m_clock.restart().asSeconds();

		m_player.update(m_deltaTime, m_input);

		m_window.clear(Color::Black);

		m_window.draw(m_tilemap);
		m_window.draw(m_player);

		m_window.display();
	}
}
