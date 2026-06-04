#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Input.h"
#include "json.hpp"


class Player : public sf::Drawable, public sf::Transformable
{
public:
	void load(std::string dataPath);

	void setPosition(sf::Vector2i pos);

	sf::Vector2i getPosition() const;

	void update(float deltaTime, Input& input);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void animate(float deltaTime);

	int m_speed;
	int m_jumpForce;
	sf::Vector2i m_position;

	int m_spriteSize;
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	int m_animationSpeed; //en sec
	int m_timeCounter;
	int m_frameCounter;
	nlohmann::json m_animations;
	nlohmann::json m_active_animation;
};

