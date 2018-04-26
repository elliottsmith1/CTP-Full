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

	void SpawnMap();	//spawn map tiles
	void SpawnFood(int _id);	//place food
	void SpawnWater();	//spawn lake
	void Update();	//game update

	//getters
	int GetMapSize();
	sf::RectangleShape* GetTile(int _i);

private:
	//grid size
	int grid_height = 50;
	int grid_width = 70;
	std::vector<sf::RectangleShape> map_tiles;	//tiles
	std::vector<int> food_ids;	//food positions

	//number of lakes and food tiles to spawn
	int num_lakes = 6;
	int num_food = 10;
};

#pragma once
