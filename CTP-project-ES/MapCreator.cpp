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
			shape.setOutlineThickness(1);
			shape.setFillColor(sf::Color::Green);
			shape.setPosition(width, height);

			map_tiles.push_back(shape);

			width += 20.0f;
		}
		height += 20.0f;
		width = 0.0f;
	}
	SpawnFood();
}

void MapCreator::SpawnFood()
{
	map_tiles[current_food_id].setFillColor(sf::Color::Green);

	current_food_id = rand() % map_tiles.size();	

	map_tiles[current_food_id].setFillColor(sf::Color::Red);
}

bool MapCreator::CheckCollision(sf::RectangleShape object1, sf::RectangleShape object2)
{
	if (object1.getGlobalBounds().intersects(object2.getGlobalBounds()))
	{
		return true;
	}

	return false;
}

bool MapCreator::CheckFood(sf::RectangleShape object1)
{
	if (CheckCollision(object1, map_tiles[current_food_id]))
	{
		return true;
	}

	return false;
}

sf::Vector2f MapCreator::GetFoodPos()
{
	return map_tiles[current_food_id].getPosition();
}

int MapCreator::GetMapSize()
{
	return map_tiles.size();
}

sf::RectangleShape* MapCreator::GetTile(int _i)
{
	return &map_tiles[_i];
}
