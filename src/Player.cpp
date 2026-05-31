#include "Player.h"
#include <iostream>
#include <fstream>
#include "json.hpp"

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
        std::cerr << "Erreur : Fichier JSON invalide - champs requis manquants" << std::endl;
        return;
    }

    m_speed = data["movement"]["speed"];
    m_jumpForce = data["movement"]["jump_force"];
	m_spriteSize = data["render"]["sprite_size"];
	m_animationSpeed = data["animation"]["animation_speed"];

    if (!m_texture.loadFromFile(data["render"]["texture"]))
    {
        std::cerr << "Erreur : Echec de chargement de la texture '" << data["render"]["texture"] << "'" << std::endl;
        return;
    }
	m_sprite.setTexture(m_texture);
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

void Player::update(Input& input)
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
