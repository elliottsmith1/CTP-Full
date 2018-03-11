#include <SFML/Graphics.hpp>

#include <vector>

class MapCreator
{
public:
	MapCreator() = default;
	~MapCreator() = default;

	void Update();
	void SpawnMap();
	int GetMapSize();
	sf::RectangleShape GetTile(int _i);

private:
	int grid_height = 30;
	int grid_width = 40;
	std::vector<sf::RectangleShape> map_tiles;
	sf::RectangleShape current_food;
};

#pragma once
