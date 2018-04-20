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
	bool potential = false;
	int new_food;
	int near_dis = 400;

	while (!potential)
	{
		potential = true;

		new_food = rand() % map_tiles.size();

		if (map_tiles[current_food_id].getPosition().x < map_tiles[new_food].getPosition().x + near_dis)
		{
			if (map_tiles[current_food_id].getPosition().x > map_tiles[new_food].getPosition().x - near_dis)
			{
				if (map_tiles[current_food_id].getPosition().y < map_tiles[new_food].getPosition().y + near_dis)
				{
					if (map_tiles[current_food_id].getPosition().y > map_tiles[new_food].getPosition().y - near_dis)
					{
						if (map_tiles[new_food].getFillColor() != sf::Color::Green)
						{
							potential = false;
						}
					}
				}
			}
		}
	}

	current_food_id = new_food;

	map_tiles[current_food_id].setFillColor(sf::Color::Red);
}

void MapCreator::Update()
{
	if (map_tiles[current_food_id].getFillColor() != sf::Color::Red)
	{
		SpawnFood();
	}
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

sf::RectangleShape MapCreator::GetCurrentFood()
{
	return map_tiles[current_food_id];
}
