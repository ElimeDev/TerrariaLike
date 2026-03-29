#include "TileMap.h"
#include <fstream>
#include "json.hpp"

using namespace sf;
using namespace std;

void TileMap::load(std::string filePath)
{
}

Tile TileMap::getTile(int x, int y) const
{
    return Tile();
}

bool TileMap::isSolid(int x, int y) const
{
    return false;
}

int TileMap::getWidth() const
{
    return m_width;
}

int TileMap::getHeight() const
{
    return m_height;
}

int TileMap::getTileSize() const
{
    return m_tileSize;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // on applique la transformation
    states.transform *= getTransform();

    // on applique la texture du tileset
    states.texture = &m_tileset;

    // et on dessine enfin le tableau de vertex
    target.draw(m_vertices, states);
}