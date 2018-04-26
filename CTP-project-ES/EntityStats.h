#ifndef _ENTITY_STATS_H_
#define _ENTITY_STATS_H_

#include <SFML/Graphics.hpp>

struct EntityStats
{
	//all relavent entity data to pass beteen VMs
	float food = 100.0f;							// 0	hunger value
	bool food_in_sight = false;						// 1	if can see food *deprecated*
	std::vector<sf::RectangleShape*> game_objects;	// 2	all game objects in scene
	float speed = 1.0f;								// 3	movement speed
	float health = 100;								// 4	current health
	float pos_x = 0.0f;								// 5	current x position
	float pos_y = 0.0f;								// 6	current y position
	float target_x = 700.0f;						// 7	target x position
	float target_y = 500.0f;						// 8	target y position
	std::vector<sf::RectangleShape*> nearby_objects;// 9	nearby game objects
	sf::RectangleShape* food_tile;					// 10	reference to food *deprecated*
	float sight = 150.0f;							// 11	//sight radius
	float thirst = 300.0f;							// 12	//thirst value
	bool thirsty = false;							// 13	//if thirsty
};
#endif