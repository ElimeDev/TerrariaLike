#include "TileMap.h"
#include <fstream>
#include "json.hpp"

using namespace sf;
using namespace std;
using json = nlohmann::json;

void TileMap::load(std::string filePath)
{
    ifstream f(filePath);
    json data = json::parse(f);
    
    //verif de la validité du json
    if (!(data.contains("width") and
        data.contains("height") and
        data.contains("tilesize") and
        data.contains("tileset") and
        data.contains("tile_defs") and
        data.contains("tiles")))
    {
        std::cerr << "Erreur : Fichier JSON invalide - champs requis manquants" << std::endl;
        return;
    }

    try
    {
        m_width = data["width"].get<int>();
        m_height = data["height"].get<int>();
        m_tilesize = data["tilesize"].get<int>();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur : Conversion JSON invalide - " << e.what() << std::endl;
        return;
    }

    std::string tilesetPath = data["tileset"].get<std::string>();
    if (!m_tileset.loadFromFile(tilesetPath))
    {
        std::cerr << "Erreur : Echec de chargement du tileset '" << tilesetPath << "'" << std::endl;
        return;
    }

    // Allocation du tableau de tiles
    m_tiles.clear();
    m_tiles.resize(m_width, std::vector<Tile>(m_height));

    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_height; j++)
        {
            try
            {
                int type = data["tiles"][j][i].get<int>();

                if (type < 0 || type >= data["tile_defs"].size())
                {
                    std::cerr << "Erreur : Type de tile invalide " << type << " à la position (" << i << ", " << j << ")" << std::endl;
                    return;
                }

                int tx = data["tile_defs"][type]["tx"].get<int>();
                int ty = data["tile_defs"][type]["ty"].get<int>();
                bool solid = data["tile_defs"][type]["solid"].get<bool>();

                m_tiles[i][j] = Tile{ sf::Vector2i(tx, ty), solid };
            }
            catch (const std::exception& e)
            {
                std::cerr << "Erreur : Lecture des données de tile à (" << i << ", " << j << ") - " << e.what() << std::endl;
                return;
            }
        }
    }

    // Remplissage du VertexArray
    m_vertices.clear();
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(m_width * m_height * 4);

    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_height; j++)
        {
            Tile& tile = m_tiles[i][j];

            // Indice du quad dans le vertex array
            int quadIndex = (j * m_width + i) * 4;

            // Positions en pixels
            float posX = i * m_tilesize;
            float posY = j * m_tilesize;

            // Texture coordinates (UVs)
            float uvX = tile.textureID.x * m_tilesize;
            float uvY = tile.textureID.y * m_tilesize;

            // Les 4 vertices du quad
            m_vertices[quadIndex].position = sf::Vector2f(posX, posY);
            m_vertices[quadIndex].texCoords = sf::Vector2f(uvX, uvY);

            m_vertices[quadIndex + 1].position = sf::Vector2f(posX + m_tilesize, posY);
            m_vertices[quadIndex + 1].texCoords = sf::Vector2f(uvX + m_tilesize, uvY);

            m_vertices[quadIndex + 2].position = sf::Vector2f(posX + m_tilesize, posY + m_tilesize);
            m_vertices[quadIndex + 2].texCoords = sf::Vector2f(uvX + m_tilesize, uvY + m_tilesize);

            m_vertices[quadIndex + 3].position = sf::Vector2f(posX, posY + m_tilesize);
            m_vertices[quadIndex + 3].texCoords = sf::Vector2f(uvX, uvY + m_tilesize);
        }
    }
}

Tile TileMap::getTile(int x, int y) const
{
    return m_tiles[x][y];
}

bool TileMap::isSolid(int x, int y) const
{
    return m_tiles[x][y].isSolid;
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
    return m_tilesize;
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