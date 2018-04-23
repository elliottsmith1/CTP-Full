#include <SFML/Graphics.hpp>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>

class MapCreator
{
public:
	MapCreator() = default;
	~MapCreator() = default;

	void SpawnMap();
	void SpawnFood();
	void SpawnWater();

	void Update();

	sf::Vector2f GetFoodPos();
	int GetMapSize();
	sf::RectangleShape* GetTile(int _i);
	sf::RectangleShape GetCurrentFood();

private:
	int grid_height = 50;
	int grid_width = 70;
	std::vector<sf::RectangleShape> map_tiles;
	int current_food_id;
};

#pragma once
