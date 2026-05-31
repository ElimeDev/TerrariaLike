#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Input.h"


class Player : public sf::Drawable, public sf::Transformable
{
public:
	void load(std::string dataPath);

	void setPosition(sf::Vector2i pos);

	sf::Vector2i getPosition() const;

	void update(Input& input);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int m_speed;
	int m_jumpForce;
	int m_spriteSize;
	int m_animationSpeed; //en sec
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2i m_position;
};

