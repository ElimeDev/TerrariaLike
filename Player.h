#pragma once

#include <SFML/Graphics.hpp>
#include <string>


class Player
{
public:
	Player(std::string dataPath);

private:


	int m_speed;
	int m_jumpForce;
	int m_spriteSize;
	int animationSpeed;
	sf::Sprite m_sprite;
};

