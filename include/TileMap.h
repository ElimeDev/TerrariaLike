#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	//position is center position, size is number of tiles on (x, y)
	TileMap(sf::Vector2f position, sf::Vector2f size, int tileSize, std::string tileSetPath, std::string tileMapDataPath, std::string tileMapCollisionDataPath);
	~TileMap();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//position of each tile in the tileset
	std::vector<std::vector<sf::Vector2f>> tileMapData;
	//collision data
	std::vector<std::vector<int>> tileMapCollisionData;
};

