#ifndef _ENTITY_STATS_H_
#define _ENTITY_STATS_H_

#include <SFML/Graphics.hpp>

struct EntityStats
{
	float food = 100.0f;							// 0
	bool food_in_sight = false;						// 1	
	std::vector<sf::RectangleShape*> map_tiles;		// 2
	float speed = 1.0f;								// 3
	float health = 100;								// 4

};
#endif