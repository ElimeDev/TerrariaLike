#include "Game.h"
#include "json.hpp"
#include <fstream>

using namespace sf;

Game::Game(std::string levelPath) : m_window(sf::VideoMode(810, 612), "TerrariaLike", sf::Style::Titlebar | sf::Style::Close), m_deltaTime(0.f)
{
	std::ifstream f(levelPath);
	nlohmann::json data = nlohmann::json::parse(f);
	m_tilemap.load(data["tilemap"]);
	m_player.load(data["player_data"]);
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

		m_player.update(m_deltaTime, m_input, m_tilemap);

		m_window.clear(Color::Black);

		m_window.draw(m_tilemap);
		m_window.draw(m_player);

		m_window.display();
	}
}
