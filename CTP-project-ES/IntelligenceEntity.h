#include <SFML/Graphics.hpp>

#include <vector>

#include "EntityStats.h"

class IntelligenceEntity
{
public:
	IntelligenceEntity();
	~IntelligenceEntity();

	//getters
	sf::RectangleShape GetEntity();
	sf::RectangleShape* GetEntityShape();
	sf::RectangleShape GetUI(int _i);
	sf::Text GetName();
	float GetHealth();
	int GetUISize();
	EntityStats* GetStats();

	//setters
	void SetStats(EntityStats* _stats);

	void InitShapes();	//initialise shapes
	void UpdateUI();	//update UI shapes
	void Sight();	//update sight
	void Behaviour();	//execute behaviours
	void MoveEntity(float _offsetX, float _offsetY);	//move shapes
	void BoundingBox();	//check if in range of environment 
	void Update();	//game update

private:
	//UI shapes
	sf::RectangleShape health_UI;
	sf::RectangleShape hunger_UI;
	sf::RectangleShape thirst_UI;
	sf::RectangleShape health_outline;
	sf::RectangleShape hunger_outline;
	sf::RectangleShape thirst_outline;

	//entity shape
	sf::RectangleShape entity_shape;
	
	//name tag
	sf::Text name;
	sf::Font name_font;

	//UI
	std::vector<sf::RectangleShape*> shape_UI_elements;

	//reference to stats
	EntityStats* stats;
};

#pragma once
