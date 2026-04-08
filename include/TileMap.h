#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Tile.h"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    void load(std::string filePath);

    Tile getTile(int x, int y) const;
    bool isSolid(int x, int y) const;

    int getWidth() const;
    int getHeight() const;
    int getTileSize() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    int m_width, m_height, m_tilesize;
    std::vector<std::vector<Tile>> m_tiles;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};