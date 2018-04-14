#include <SFML/Graphics.hpp>
#include <vector>

#include "EntityStats.h"

class IntelligenceEntity
{
public:
	IntelligenceEntity();
	~IntelligenceEntity();

	sf::RectangleShape* GetEntity();
	sf::RectangleShape GetUI(int _i);
	sf::RectangleShape* GetView();

	EntityStats* GetStats();

	void SetStats(EntityStats* _stats);
	void SetFoodInSight(bool _sight);
	void SetFoodPos(sf::Vector2f _pos);

	void Behaviour();
	void MoveEntity(float _offsetX, float _offsetY);
	void BoundingBox();
	void Update();
	bool CheckCollision(sf::RectangleShape object1, sf::RectangleShape object2);
	void NearbyObjects();

private:
	sf::RectangleShape health_UI;
	sf::RectangleShape hunger_UI;
	sf::RectangleShape entity_shape;
	sf::RectangleShape view;

	std::vector<sf::RectangleShape*> shape_UI_elements;

	EntityStats* stats;

	sf::Vector2f food_pos;
};

#pragma once
