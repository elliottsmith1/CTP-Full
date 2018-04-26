#include <SFML/Graphics.hpp>

#include "IntelligenceEntity.h"

class Enemy
{
public:
	Enemy(IntelligenceEntity* _entity);
	~Enemy() = default;

	void InitShapes();	//initialise shapes
	void MoveEnemy(float _offsetX, float _offsetY);	//move shapes
	void Update();	//game update
	void NewTarget(float _x_pos, float _y_pos);	//target position 
	void RandomTarget();	//random target position

	//getters
	std::vector<sf::RectangleShape*> GetEnemyShapes();

private:
	//shapes
	sf::RectangleShape enemy_shape;
	sf::RectangleShape enemy_shape_2;

	//entity reference
	IntelligenceEntity* entity;

	//shapes
	std::vector<sf::RectangleShape*> enemy_shapes;

	//target positions
	float y_target;
	float x_target;

	//movement speed
	float speed = 0.5f;

	//sight radius
	float sight_value = 100.0f;
};