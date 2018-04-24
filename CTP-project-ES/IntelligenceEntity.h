#include <SFML/Graphics.hpp>

#include <vector>

#include "EntityStats.h"

class IntelligenceEntity
{
public:
	IntelligenceEntity();
	~IntelligenceEntity();

	sf::RectangleShape GetEntity();
	sf::RectangleShape* GetEntityShape();
	sf::RectangleShape GetUI(int _i);
	sf::Text GetName();
	float GetHealth();

	int GetUISize();
	EntityStats* GetStats();

	void SetStats(EntityStats* _stats);

	void InitShapes();
	void UpdateUI();
	void Sight();
	void Behaviour();
	void MoveEntity(float _offsetX, float _offsetY);
	void BoundingBox();
	void Update();
	bool CheckCollision(sf::RectangleShape object1, sf::RectangleShape object2);

private:
	sf::RectangleShape health_UI;
	sf::RectangleShape hunger_UI;
	sf::RectangleShape thirst_UI;
	sf::RectangleShape health_outline;
	sf::RectangleShape hunger_outline;
	sf::RectangleShape thirst_outline;
	sf::RectangleShape entity_shape;
	
	sf::Text name;
	sf::Font name_font;

	std::vector<sf::RectangleShape*> shape_UI_elements;

	EntityStats* stats;
};

#pragma once
