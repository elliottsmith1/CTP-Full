#include "IntelligenceEntity.h"

IntelligenceEntity::IntelligenceEntity()
{	
	stats = new EntityStats;

	InitShapes();
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

int IntelligenceEntity::GetUISize()
{
	return shape_UI_elements.size();
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

void IntelligenceEntity::InitShapes()
{
	//AI visual representation
	entity_shape.setSize(sf::Vector2f(50, 50));
	entity_shape.setOutlineColor(sf::Color::Black);
	entity_shape.setOutlineThickness(2);
	entity_shape.setFillColor(sf::Color::Yellow);
	entity_shape.setOrigin(20, 20);
	entity_shape.setPosition(400, 200);

	stats->pos_x = entity_shape.getPosition().x;
	stats->pos_y = entity_shape.getPosition().y;
	stats->target_x = stats->pos_x;
	stats->target_y = stats->pos_y;

	//UI
	health_outline.setSize(sf::Vector2f(18, 40));
	health_outline.setOutlineColor(sf::Color::Black);
	health_outline.setOutlineThickness(3);
	health_outline.setFillColor(sf::Color::Transparent);
	health_outline.setPosition(385, 185);
	shape_UI_elements.push_back(&health_outline);

	hunger_outline.setSize(sf::Vector2f(18, 40));
	hunger_outline.setOutlineColor(sf::Color::Black);
	hunger_outline.setOutlineThickness(3);
	hunger_outline.setFillColor(sf::Color::Transparent);
	hunger_outline.setPosition(407, 185);
	shape_UI_elements.push_back(&hunger_outline);

	health_UI.setSize(sf::Vector2f(18, 40));
	health_UI.setFillColor(sf::Color(255, 0, 0, 255));
	health_UI.setPosition(385, 185);
	shape_UI_elements.push_back(&health_UI);

	hunger_UI.setSize(sf::Vector2f(18, 40));
	hunger_UI.setFillColor(sf::Color(255, 102, 0, 255));
	hunger_UI.setPosition(407, 185);
	shape_UI_elements.push_back(&hunger_UI);

	view.setSize(sf::Vector2f(300, 300));
	view.setOrigin(150, 150);
	view.setPosition(400, 200);
}

void IntelligenceEntity::UpdateUI()
{
	float perc = stats->food / 100;
	perc * 30.0f;
	hunger_UI.setScale(1, perc);

	perc = stats->health / 100;
	perc * 30.0f;
	health_UI.setScale(1, perc);
}

void IntelligenceEntity::Sight()
{
	stats->nearby_objects.clear();

	if (stats->game_objects.size() > 0)
	{
		float sight_value = stats->sight;

		for (int i = 0; i < stats->game_objects.size(); i++)
		{
			if (stats->pos_x < stats->game_objects[i]->getPosition().x + sight_value)
			{
				if (stats->pos_x > stats->game_objects[i]->getPosition().x - sight_value)
				{
					if (stats->pos_y < stats->game_objects[i]->getPosition().y + sight_value)
					{
						if (stats->pos_y > stats->game_objects[i]->getPosition().y - sight_value)
						{
							stats->nearby_objects.push_back(stats->game_objects[i]);
						}
					}
				}
			}
		}
	}
}

void IntelligenceEntity::Behaviour()
{
	if (stats->food > 100)
	{
		stats->food = 100;
	}

	Sight();

	if (entity_shape.getPosition().y < stats->pos_y)
	{
		MoveEntity(0, stats->speed);
	}

	if (entity_shape.getPosition().y > stats->pos_y)
	{
		MoveEntity(0, -stats->speed);
	}

	if (entity_shape.getPosition().x < stats->pos_x)
	{
		MoveEntity(stats->speed, 0);
	}

	if (entity_shape.getPosition().x > stats->pos_x)
	{
		MoveEntity(-stats->speed, 0);
	}
}

void IntelligenceEntity::MoveEntity(float _offsetX, float _offsetY)
{
	entity_shape.move(_offsetX, _offsetY);
	view.move(_offsetX, _offsetY);

	hunger_outline.move(_offsetX, _offsetY);
	hunger_UI.move(_offsetX, _offsetY);

	health_outline.move(_offsetX, _offsetY);
	health_UI.move(_offsetX, _offsetY);

	if (_offsetX != 0)
	{
		stats->pos_x = entity_shape.getPosition().x;
	}

	if (_offsetY != 0)
	{
		stats->pos_y = entity_shape.getPosition().y;
	}
}

void IntelligenceEntity::BoundingBox()
{
	if (entity_shape.getPosition().x < 0)
	{
		MoveEntity(stats->speed, 0);
	}

	if (entity_shape.getPosition().x > 775)
	{
		MoveEntity(-stats->speed, 0);
	}

	if (entity_shape.getPosition().y < 0)
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
	UpdateUI();

	if (stats->health < 1)
	{
		entity_shape.setFillColor(sf::Color::Black);
	}

	else
	{
		Behaviour();
		BoundingBox();
		//NearbyObjects();
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
	for (int i = 0; i < stats->nearby_objects.size(); i++)
	{
		if (CheckCollision(entity_shape, *stats->game_objects[i]))
		{
			if (stats->game_objects[i]->getFillColor() == sf::Color::Red)
			{
				stats->game_objects[i]->setFillColor(sf::Color::Green);
			}
		}
	}
}



