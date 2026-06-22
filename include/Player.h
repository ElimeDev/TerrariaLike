#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Input.h"
#include "json.hpp"
#include "TileMap.h"


class Player : public sf::Drawable, public sf::Transformable
{
	struct InputAction
	{
		int dir;
		bool jump;
	};

public:
	void load(std::string dataPath);

	void setPosition(sf::Vector2f pos);

	sf::Vector2f getPosition() const;

	void update(float deltaTime, Input& input, TileMap& tilemap);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void animate(float deltaTime);
	InputAction handle_input(Input& input);
	void resolveCollisionsX(TileMap& tilemap);
	void resolveCollisionsY(TileMap& tilemap);

	int m_speed;
	int m_jumpForce;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	bool m_onGround = false;

	int m_spriteSize;
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	float m_animationSpeed; //en sec
	float m_timeCounter;
	int m_frameCounter;
	nlohmann::json m_animations;
	nlohmann::json m_active_animation;
};

