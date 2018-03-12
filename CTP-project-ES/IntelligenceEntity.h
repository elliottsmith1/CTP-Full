#include <SFML/Graphics.hpp>

#include "EntityStats.h"

class IntelligenceEntity
{
public:
	IntelligenceEntity();
	~IntelligenceEntity();

	sf::RectangleShape* GetEntity();
	sf::RectangleShape* GetView();

	EntityStats* GetStats();

	void SetFoodInSight(bool _sight);
	void SetFoodPos(sf::Vector2f _pos);

	void InterpretFSM(int _id, int _state);
	void MoveEntity(float _offsetX, float _offsetY);
	void BoundingBox();
	void Update();	

private:
	sf::RectangleShape entity_shape;
	sf::RectangleShape view;

	EntityStats* stats;

	float speed = 1.0f;

	bool food_in_sight;
	sf::Vector2f food_pos;
};

#pragma once
