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
	bool CheckCollision(sf::RectangleShape object1, sf::RectangleShape object2);
	bool CheckFood(sf::RectangleShape object1);
	int GetMapSize();
	sf::RectangleShape GetTile(int _i);

private:
	int grid_height = 30;
	int grid_width = 40;
	std::vector<sf::RectangleShape> map_tiles;
	sf::RectangleShape current_food;
	int current_food_id;
};

#pragma once
