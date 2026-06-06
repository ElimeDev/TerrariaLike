#include "Player.h"
#include <iostream>
#include <fstream>

using namespace sf;
using namespace std;
using json = nlohmann::json;

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

void Player::setPosition(sf::Vector2i pos)
{
    m_position = pos;
    m_sprite.setPosition(static_cast<sf::Vector2f>(pos)); // Update sprite position
}

sf::Vector2i Player::getPosition() const
{
	return m_position;
}

void Player::update(float deltaTime, Input& input)
{
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