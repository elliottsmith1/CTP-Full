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
	void SpawnFood(int _id);
	void SpawnWater();

	void Update();

	int GetMapSize();
	sf::RectangleShape* GetTile(int _i);

private:
	int grid_height = 50;
	int grid_width = 70;
	std::vector<sf::RectangleShape> map_tiles;
	std::vector<int> food_ids;

	int num_lakes = 6;
	int num_food = 6;
};

#pragma once
