#include "MapCreator.h"

void MapCreator::SpawnMap()
{
	srand(time(NULL)); // get random seed

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

	SpawnWater();
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

	map_tiles[current_food_id].setFillColor(sf::Color(255, 102, 0, 255));
}

void MapCreator::SpawnWater()
{
	int water_num = 0;
	bool spawn_water = true;

	int max_water = 3;

	int near_dis = 25;
	int water_id = rand() % map_tiles.size();

	map_tiles[water_id].setFillColor(sf::Color::Blue);

	while (spawn_water)
	{
		for (int j = 0; j < map_tiles.size(); j++)
		{
			if (map_tiles[j].getFillColor() == sf::Color::Blue)
			{
				for (int l = 0; l < map_tiles.size(); l++)
				{
					if (map_tiles[l].getPosition().x < map_tiles[j].getPosition().x + near_dis)
					{
						if (map_tiles[l].getPosition().x > map_tiles[j].getPosition().x - near_dis)
						{
							if (map_tiles[l].getPosition().y < map_tiles[j].getPosition().y + near_dis)
							{
								if (map_tiles[l].getPosition().y > map_tiles[j].getPosition().y - near_dis)
								{
									int spread_chance = rand() % 100;

									if (spread_chance < 15)
									{
										if (water_num < max_water)
										{
											map_tiles[l].setFillColor(sf::Color::Blue);

											water_num++;
										}

										if (water_num >= max_water)
										{
											spawn_water = false;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void MapCreator::Update()
{
	if (map_tiles[current_food_id].getFillColor() != sf::Color(255, 102, 0, 255))
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
