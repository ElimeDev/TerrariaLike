#include "Game.h"

using namespace sf;

Game::Game() : m_window(sf::VideoMode(810, 612), "TerrariaLike", sf::Style::Titlebar | sf::Style::Close)
{
	
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
			if (event.type == Event::Closed)
			{
				m_window.close();
			}
		}

		m_window.clear(Color::Black);

		

		m_window.display();
	}
}
