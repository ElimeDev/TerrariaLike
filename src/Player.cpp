#include "Player.h"
#include <iostream>
#include <fstream>

using namespace sf;
using namespace std;
using json = nlohmann::json;

const float GRAVITY = 20.f;

void Player::load(std::string dataPath)
{
    ifstream f(dataPath);
    json data = json::parse(f);

    //verif de la validité du json
    if (!(data.contains("movement") and
        data.contains("render") and
        data.contains("animation") and
        data["movement"].contains("speed") and
        data["movement"].contains("jump_force") and
        data["render"].contains("texture") and
        data["render"].contains("sprite_size") and
        data["animation"].contains("idle") and
        data["animation"].contains("animation_speed") and
        data["animation"].contains("walk_right") and
        data["animation"].contains("walk_left") and
        data["animation"].contains("jump") and
        data["animation"].contains("fall")))
    {
        throw std::runtime_error("[Entity] JSON invalide : champs requis manquants");
        return;
    }

    m_speed = data["movement"]["speed"];
    m_jumpForce = data["movement"]["jump_force"];
	m_spriteSize = data["render"]["sprite_size"];
	m_animationSpeed = data["animation"]["animation_speed"];
    m_animations = data["animation"];
	m_active_animation = m_animations["idle"];

	m_timeCounter = 0;
	m_frameCounter = 0;

    if (!m_texture.loadFromFile(data["render"]["texture"]))
    {
        throw std::runtime_error("Erreur : Echec de chargement de la texture");
        return;
    }
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(IntRect(
		m_active_animation[m_frameCounter][0].get<int>() * m_spriteSize,
		m_active_animation[m_frameCounter][1].get<int>() * m_spriteSize,
		m_spriteSize,
		m_spriteSize
	));
}

void Player::setPosition(sf::Vector2f pos)
{
    m_position = pos;
    m_sprite.setPosition(static_cast<sf::Vector2f>(pos)); // Update sprite position
}

sf::Vector2f Player::getPosition() const
{
	return m_position;
}

void Player::update(float deltaTime, Input& input, TileMap& tilemap)
{
    InputAction inputAction = handle_input(input);

    m_velocity.x = m_speed * inputAction.dir;
    m_velocity.y += GRAVITY * deltaTime;

    // X séparé
    m_position.x += m_velocity.x * deltaTime;
    resolveCollisionsX(tilemap);

    // Y séparé
    m_position.y += m_velocity.y * deltaTime;
    resolveCollisionsY(tilemap);

    m_sprite.setPosition(m_position);
    animate(deltaTime);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

void Player::animate(float deltaTime)
{
	m_timeCounter += deltaTime;
	if (m_timeCounter >= m_animationSpeed)
	{
		m_timeCounter = 0;
		m_frameCounter = (m_frameCounter + 1) % m_active_animation.size();
		m_sprite.setTextureRect(IntRect(
			m_active_animation[m_frameCounter][0].get<int>() * m_spriteSize,
			m_active_animation[m_frameCounter][1].get<int>() * m_spriteSize,
			m_spriteSize,
			m_spriteSize
		));
	}
}

Player::InputAction Player::handle_input(Input& input)
{
    int dir = 0;
    if (input.getButton().right)
        dir = 1;
    else if (input.getButton().left)
        dir = -1;
    else
        dir = 0;
    return InputAction(dir, input.getButton().jump);
}

void Player::resolveCollisionsX(TileMap& tilemap)
{
    int tileSize = tilemap.getTileSize();
    int left = (int)m_position.x / tileSize;
    int right = ((int)m_position.x + m_spriteSize - 1) / tileSize;
    int top = (int)m_position.y / tileSize;
    int bottom = ((int)m_position.y + m_spriteSize - 1) / tileSize;

    if (m_velocity.x < 0 && (tilemap.isSolid(left, top) || tilemap.isSolid(left, bottom)))
    {
        m_position.x = (left + 1) * tileSize;
        m_velocity.x = 0;
    }
    if (m_velocity.x > 0 && (tilemap.isSolid(right, top) || tilemap.isSolid(right, bottom)))
    {
        m_position.x = right * tileSize - m_spriteSize;
        m_velocity.x = 0;
    }
}

void Player::resolveCollisionsY(TileMap& tilemap)
{
    int tileSize = tilemap.getTileSize();
    int left = (int)m_position.x / tileSize;
    int right = ((int)m_position.x + m_spriteSize - 1) / tileSize;
    int top = (int)m_position.y / tileSize;
    int bottom = ((int)m_position.y + m_spriteSize - 1) / tileSize;

    if (m_velocity.y > 0 && (tilemap.isSolid(left, bottom) || tilemap.isSolid(right, bottom)))
    {
        m_position.y = bottom * tileSize - m_spriteSize;
        m_velocity.y = 0;
        m_onGround = true;
    }
    else if (m_velocity.y < 0 && (tilemap.isSolid(left, top) || tilemap.isSolid(right, top)))
    {
        m_position.y = (top + 1) * tileSize;
        m_velocity.y = 0;
    }
    else
    {
        m_onGround = false;
    }
}
