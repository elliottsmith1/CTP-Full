#include "IntelligenceEntity.h"

IntelligenceEntity::IntelligenceEntity()
{
	//AI visual representation
	entity_shape.setSize(sf::Vector2f(50, 50));
	entity_shape.setOutlineColor(sf::Color::Black);
	entity_shape.setOutlineThickness(2);
	entity_shape.setFillColor(sf::Color::Yellow);
	entity_shape.setOrigin(20, 20);
	entity_shape.setPosition(400, 200);
	
	view.setSize(sf::Vector2f(300, 300));
	view.setOrigin(150, 150);
	view.setPosition(400, 200);

	stats = new EntityStats;
}

IntelligenceEntity::~IntelligenceEntity()
{
	delete stats;
}

sf::RectangleShape* IntelligenceEntity::GetEntity()
{
	return &entity_shape;
}

sf::RectangleShape* IntelligenceEntity::GetView()
{
	return &view;
}

EntityStats * IntelligenceEntity::GetStats()
{
	return stats;
}


void IntelligenceEntity::SetFoodPos(sf::Vector2f _pos)
{
	food_pos = _pos;
}

void IntelligenceEntity::InterpretFSM(int _id, int _state)
{
	srand(time(NULL));
	int random_num = rand() % 4;

	switch (_id)
	{
	case 0:
		switch (_state)
		{
		case 0:
			return;
		case 1:
			speed = 1.0f;			
			break;
		case 2:
			speed = 1.5f;			
			break;
		case 3:
			speed = 2.0f;
			break;
		case 4:
			speed = 3.0f;
			break;
		default:
			break;
		}

		switch (random_num)
		{
		case 0:
			MoveEntity(speed, 0);
			break;
		case 1:
			MoveEntity(-speed, 0);
			break;
		case 2:
			MoveEntity(0, speed);
			break;
		case 3:
			MoveEntity(0, -speed);
			break;
		}
		break;
	case 1:
		switch (_state)
		{
		case 1:
			if (food_pos.x > entity_shape.getPosition().x)
			{
				MoveEntity(speed, 0);
			}
			if (food_pos.x < entity_shape.getPosition().x)
			{
				MoveEntity(-speed, 0);
			}
			if (food_pos.y > entity_shape.getPosition().y)
			{
				MoveEntity(0, speed);
			}
			if (food_pos.y < entity_shape.getPosition().y)
			{
				MoveEntity(0, -speed);
			}	
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void IntelligenceEntity::MoveEntity(float _offsetX, float _offsetY)
{
	entity_shape.move(_offsetX, _offsetY);
	view.move(_offsetX, _offsetY);
}

void IntelligenceEntity::BoundingBox()
{
	if (entity_shape.getPosition().x < 25)
	{
		MoveEntity(speed, 0);
	}

	if (entity_shape.getPosition().x > 775)
	{
		MoveEntity(-speed, 0);
	}

	if (entity_shape.getPosition().y < 25)
	{
		MoveEntity(0, speed);
	}

	if (entity_shape.getPosition().y > 575)
	{
		MoveEntity(0, -speed);
	}
}

void IntelligenceEntity::Update()
{
	if (stats->food >= 0.01f)
	{
		stats->food -= 0.01f;
	}

	BoundingBox();	
	NearbyObjects();

}

bool IntelligenceEntity::CheckCollision(sf::RectangleShape object1, sf::RectangleShape object2)
{
	if (object1.getGlobalBounds().intersects(object2.getGlobalBounds()))
	{
		return true;
	}

	return false;
}

void IntelligenceEntity::NearbyObjects()
{
	for (int i = 0; i < stats->map_tiles.size(); i++)
	{
		if (CheckCollision(view, *stats->map_tiles[i]))
		{
			if (stats->map_tiles[i]->getFillColor() == sf::Color::Red)
			{
				if (!stats->food_in_sight)
				{
					stats->food_in_sight = true;
					food_pos = stats->map_tiles[i]->getPosition();
				}

				if (CheckCollision(entity_shape, *stats->map_tiles[i]))
				{
					stats->map_tiles[i]->setFillColor(sf::Color::Green);
					stats->food += 25;
					stats->food_in_sight = false;

					if (stats->food > 100)
					{
						stats->food = 100;
					}
				}
			}
		}
	}

}



