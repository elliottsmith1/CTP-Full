#include "Enemy.h"

Enemy::Enemy(IntelligenceEntity* _entity)
{
	entity = _entity;

	srand(time(NULL)); // get random seed

	InitShapes();

	RandomTarget();
}

void Enemy::InitShapes()
{
	enemy_shape.setSize(sf::Vector2f(30, 30));
	enemy_shape.setOutlineColor(sf::Color::Black);
	enemy_shape.setOutlineThickness(2);
	enemy_shape.setFillColor(sf::Color::Red);
	enemy_shape.setOrigin(15, 15);
	enemy_shape.setPosition(200, 200);
	enemy_shapes.push_back(&enemy_shape);

	enemy_shape_2.setSize(sf::Vector2f(30, 30));
	enemy_shape_2.setOutlineColor(sf::Color::Black);
	enemy_shape_2.setOutlineThickness(2);
	enemy_shape_2.setFillColor(sf::Color::Red);
	enemy_shape_2.setOrigin(15, 15);
	enemy_shape_2.setPosition(200, 200);
	enemy_shape_2.setRotation(45);
	enemy_shapes.push_back(&enemy_shape_2);
}

void Enemy::MoveEnemy(float _offsetX, float _offsetY)
{
	enemy_shape.move(_offsetX, _offsetY);	
	enemy_shape_2.move(_offsetX, _offsetY);
}

void Enemy::Update()
{
	float spin_speed = 2;
	enemy_shape.rotate(spin_speed);
	enemy_shape_2.rotate(spin_speed);

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

	if (enemy_shape.getGlobalBounds().intersects(entity->GetEntity().getGlobalBounds()))
	{
		float damaged_health = entity->GetStats()->health;
		damaged_health -= 0.1f;

		entity->GetStats()->health = damaged_health;
	}
}

void Enemy::NewTarget(float _x_pos, float _y_pos)
{
	x_target = _x_pos;
	y_target = _y_pos;
}

void Enemy::RandomTarget()
{
	float random_x = rand() % 1475;
	float random_y = rand() % 975;

	x_target = random_x;
	y_target = random_y;
}

std::vector<sf::RectangleShape*> Enemy::GetEnemyShapes()
{
	return enemy_shapes;
}
