#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#include "MapCreator.h"

void MapCreator::SpawnMap()
{
	srand(time(NULL));

	float width = 0;
	float height = 0;

	for (int i = 0; i < grid_height; i++)
	{
		for (int j = 0; j < grid_width; j++)
		{
			sf::RectangleShape shape;
			shape.setSize(sf::Vector2f(20, 20));
			shape.setOutlineColor(sf::Color::Black);
			shape.setOutlineThickness(2);
			shape.setFillColor(sf::Color::Green);
			shape.setPosition(width, height);

			map_tiles.push_back(shape);

			width += 20.0f;
		}
		height += 20.0f;
		width = 0.0f;
	}

	int random = rand() % map_tiles.size();

	map_tiles[random].setFillColor(sf::Color::Red);
	current_food = map_tiles[random];
}

int MapCreator::GetMapSize()
{
	return map_tiles.size();
}

sf::RectangleShape MapCreator::GetTile(int _i)
{
	return map_tiles[_i];
}
