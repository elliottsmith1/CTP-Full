#ifndef _ENTITY_STATS_H_
#define _ENTITY_STATS_H_

#include <SFML/Graphics.hpp>

struct EntityStats
{
	float food = 100.0f;
	bool food_in_sight = false;
	std::vector<sf::RectangleShape*> map_tiles;

};
#endif