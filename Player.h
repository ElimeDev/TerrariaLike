#pragma once

#include <SFML/Graphics.hpp>
#include <string>


class Player : public sf::Drawable, public sf::Transformable
{
public:
	Player(std::string dataPath);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int m_speed;
	int m_jumpForce;
	int m_spriteSize;
	int animationSpeed;
	sf::Sprite m_sprite;
};

