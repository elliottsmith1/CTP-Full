#include <SFML/Graphics.hpp>

#include "IntelligenceEntity.h"

class Enemy
{
public:
	Enemy(IntelligenceEntity* _entity);
	~Enemy() = default;

	void InitShapes();
	void MoveEnemy(float _offsetX, float _offsetY);
	void Update();
	void NewTarget(float _x_pos, float _y_pos);
	void RandomTarget();

	std::vector<sf::RectangleShape*> GetEnemyShapes();

private:
	sf::RectangleShape enemy_shape;
	sf::RectangleShape enemy_shape_2;

	IntelligenceEntity* entity;

	std::vector<sf::RectangleShape*> enemy_shapes;

	float y_target;
	float x_target;

	float speed = 0.1f;

	float sight_value = 100.0f;
};