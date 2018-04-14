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

	//UI
	health_UI.setSize(sf::Vector2f(20, 50));
	health_UI.setFillColor(sf::Color(255, 0, 0, 200));
	health_UI.setPosition(20, 30);
	shape_UI_elements.push_back(&health_UI);

	hunger_UI.setSize(sf::Vector2f(20, 50));
	hunger_UI.setFillColor(sf::Color(255, 102, 0, 200));
	hunger_UI.setPosition(50, 30);
	shape_UI_elements.push_back(&hunger_UI);
	
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

sf::RectangleShape IntelligenceEntity::GetUI(int _i)
{
	return *shape_UI_elements[_i];
}

sf::RectangleShape* IntelligenceEntity::GetView()
{
	return &view;
}

EntityStats * IntelligenceEntity::GetStats()
{
	return stats;
}

void IntelligenceEntity::SetStats(EntityStats * _stats)
{
	stats = _stats;
}


void IntelligenceEntity::SetFoodPos(sf::Vector2f _pos)
{
	food_pos = _pos;
}

void IntelligenceEntity::Behaviour()
{
	if (stats->food_in_sight)
	{
		if (food_pos.x > entity_shape.getPosition().x)
		{
			MoveEntity(stats->speed, 0);
		}
		if (food_pos.x < entity_shape.getPosition().x)
		{
			MoveEntity(-stats->speed, 0);
		}
		if (food_pos.y > entity_shape.getPosition().y)
		{
			MoveEntity(0, stats->speed);
		}
		if (food_pos.y < entity_shape.getPosition().y)
		{
			MoveEntity(0, -stats->speed);
		}
	}

	else
	{
		srand(time(NULL));
		int random_num = rand() % 4;

		switch (random_num)
		{
		case 0:
			MoveEntity(stats->speed, 0);
			break;
		case 1:
			MoveEntity(-stats->speed, 0);
			break;
		case 2:
			MoveEntity(0, stats->speed);
			break;
		case 3:
			MoveEntity(0, -stats->speed);
			break;
		}
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
		MoveEntity(stats->speed, 0);
	}

	if (entity_shape.getPosition().x > 775)
	{
		MoveEntity(-stats->speed, 0);
	}

	if (entity_shape.getPosition().y < 25)
	{
		MoveEntity(0, stats->speed);
	}

	if (entity_shape.getPosition().y > 575)
	{
		MoveEntity(0, -stats->speed);
	}
}

void IntelligenceEntity::Update()
{
	float perc = stats->food / 100;
	perc * 30.0f;
	hunger_UI.setScale(1, perc);
	
	perc = stats->health / 100;
	perc * 30.0f;
	health_UI.setScale(1, perc);

	if (stats->health < 1)
	{
		entity_shape.setFillColor(sf::Color::Black);
	}

	else
	{
		Behaviour();
		BoundingBox();
		NearbyObjects();
	}

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



