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

	for (int i = 0; i < num_lakes; i++)
	{
		SpawnWater();
	}

	for (int i = 0; i < num_food; i++)
	{
		SpawnFood(i);
	}
}

void MapCreator::SpawnFood(int _id)
{
	bool potential = false;
	int new_food;
	int near_dis = 400;

	while (!potential)
	{
		potential = true;

		new_food = rand() % map_tiles.size();

		for (int i = 0; i < food_ids.size(); i++)
		{
			if (map_tiles[food_ids[i]].getPosition().x < map_tiles[new_food].getPosition().x + near_dis)
			{
				if (map_tiles[food_ids[i]].getPosition().x > map_tiles[new_food].getPosition().x - near_dis)
				{
					if (map_tiles[food_ids[i]].getPosition().y < map_tiles[new_food].getPosition().y + near_dis)
					{
						if (map_tiles[food_ids[i]].getPosition().y > map_tiles[new_food].getPosition().y - near_dis)
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
	}

	if ((_id >= food_ids.size()) || (food_ids.size() == 0))
	{
		food_ids.push_back(new_food);
	}

	else
	{
		food_ids[_id] = new_food;
	}

	map_tiles[new_food].setFillColor(sf::Color(255, 102, 0, 255));
}

void MapCreator::SpawnWater()
{
	int water_num = 0;
	int water_id; 
	bool spawn_water = true;
	bool empty_space = false;

	int max_water = 4;

	int near_dis;

	while (!empty_space)
	{
		water_id = rand() % map_tiles.size();

		if (map_tiles[water_id].getFillColor() == sf::Color::Green)
		{
			map_tiles[water_id].setFillColor(sf::Color::Blue);
			empty_space = true;
			near_dis = map_tiles[water_id].getSize().x + 1;
		}
	}

	while (spawn_water)
	{
		for (int l = 0; l < map_tiles.size(); l++)
		{
			if (map_tiles[l].getPosition().x < map_tiles[water_id].getPosition().x + near_dis)
			{
				if (map_tiles[l].getPosition().x > map_tiles[water_id].getPosition().x - near_dis)
				{
					if (map_tiles[l].getPosition().y < map_tiles[water_id].getPosition().y + near_dis)
					{
						if (map_tiles[l].getPosition().y > map_tiles[water_id].getPosition().y - near_dis)
						{
							if (map_tiles[l].getFillColor() == sf::Color::Green)
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

void MapCreator::Update()
{
	for (int i = 0; i < food_ids.size(); i++)
	{
		if (map_tiles[food_ids[i]].getFillColor() != sf::Color(255, 102, 0, 255))
		{
			SpawnFood(i);
		}
	}
}

int MapCreator::GetMapSize()
{
	return map_tiles.size();
}

sf::RectangleShape* MapCreator::GetTile(int _i)
{
	return &map_tiles[_i];
}


