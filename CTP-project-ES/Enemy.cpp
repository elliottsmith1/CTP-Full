#include "Enemy.h"

Enemy::Enemy(IntelligenceEntity* _entity)
{
	entity = _entity;

	InitShapes();

	RandomTarget();
}

void Enemy::InitShapes()
{
	//random spawn point
	float spawn_x = rand() % 1375;
	float spawn_y = rand() % 975;

	//shape initialisation
	enemy_shape.setSize(sf::Vector2f(30, 30));
	enemy_shape.setOutlineColor(sf::Color::Black);
	enemy_shape.setOutlineThickness(2);
	enemy_shape.setFillColor(sf::Color::Red);
	enemy_shape.setOrigin(15, 15);
	enemy_shape.setPosition(spawn_x, spawn_y);
	enemy_shapes.push_back(&enemy_shape);

	enemy_shape_2.setSize(sf::Vector2f(30, 30));
	enemy_shape_2.setOutlineColor(sf::Color::Black);
	enemy_shape_2.setOutlineThickness(2);
	enemy_shape_2.setFillColor(sf::Color::Red);
	enemy_shape_2.setOrigin(15, 15);
	enemy_shape_2.setPosition(spawn_x, spawn_y);
	enemy_shape_2.setRotation(45);
	enemy_shapes.push_back(&enemy_shape_2);
}

void Enemy::MoveEnemy(float _offsetX, float _offsetY)
{
	//move shapes
	enemy_shape.move(_offsetX, _offsetY);	
	enemy_shape_2.move(_offsetX, _offsetY);
}

void Enemy::Update()
{
	//spin to look scary
	float spin_speed = 5;
	enemy_shape.rotate(spin_speed);
	enemy_shape_2.rotate(spin_speed);

	//if not near to target position, move to target position
	if (enemy_shape.getPosition().y < y_target)
	{
		MoveEnemy(0, speed);
	}

	if (enemy_shape.getPosition().y > y_target)
	{
		MoveEnemy(0, -speed);
	}

	if (enemy_shape.getPosition().x < x_target)
	{
		MoveEnemy(speed, 0);
	}

	if (enemy_shape.getPosition().x > x_target)
	{
		MoveEnemy(-speed, 0);
	}

	//if near target position, new random target 
	float near_value = 5.0f;

	if (enemy_shape.getPosition().x < x_target + near_value)
	{
		if (enemy_shape.getPosition().x > x_target - near_value)
		{
			if (enemy_shape.getPosition().y < y_target + near_value)
			{
				if (enemy_shape.getPosition().y > y_target - near_value)
				{
					RandomTarget();
				}
			}
		}
	}	

	//if near entity, set target position to chase
	if (enemy_shape.getPosition().x < entity->GetEntity().getPosition().x + sight_value)
	{
		if (enemy_shape.getPosition().x > entity->GetEntity().getPosition().x - sight_value)
		{
			if (enemy_shape.getPosition().y < entity->GetEntity().getPosition().y + sight_value)
			{
				if (enemy_shape.getPosition().y > entity->GetEntity().getPosition().y - sight_value)
				{
					x_target = entity->GetEntity().getPosition().x;
					y_target = entity->GetEntity().getPosition().y;
				}
			}
		}
	}

	//if hitting entity, damage
	if (enemy_shape.getGlobalBounds().intersects(entity->GetEntity().getGlobalBounds()))
	{
		float damaged_health = entity->GetStats()->health;
		damaged_health -= 0.1f;

		entity->GetStats()->health = damaged_health;
	}
}

void Enemy::NewTarget(float _x_pos, float _y_pos)
{
	//new target pos
	x_target = _x_pos;
	y_target = _y_pos;
}

void Enemy::RandomTarget()
{
	//random target pos
	float random_x = rand() % 1375;
	float random_y = rand() % 975;

	x_target = random_x;
	y_target = random_y;
}

std::vector<sf::RectangleShape*> Enemy::GetEnemyShapes()
{
	return enemy_shapes;
}
