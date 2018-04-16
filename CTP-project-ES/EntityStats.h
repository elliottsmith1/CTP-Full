#ifndef _ENTITY_STATS_H_
#define _ENTITY_STATS_H_

#include <SFML/Graphics.hpp>

struct EntityStats
{
	float food = 100.0f;							// 0
	bool food_in_sight = false;						// 1	
	std::vector<sf::RectangleShape*> game_objects;	// 2
	float speed = 1.0f;								// 3
	float health = 100;								// 4
	float pos_x = 0.0f;								// 5
	float pos_y = 0.0f;								// 6
	float target_x = 500.0f;						// 7
	float target_y = 500.0f;						// 8
	std::vector<sf::RectangleShape*> nearby_objects;// 9
	sf::RectangleShape* food_tile;					// 10
};
#endif