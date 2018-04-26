#include "IntelligenceEntity.h"

IntelligenceEntity::IntelligenceEntity()
{	
	//initialise starting values
	stats = new EntityStats;

	InitShapes();
}

IntelligenceEntity::~IntelligenceEntity()
{
	delete stats;
}

sf::RectangleShape IntelligenceEntity::GetEntity()
{
	return entity_shape;
}

sf::RectangleShape * IntelligenceEntity::GetEntityShape()
{
	return &entity_shape;
}

sf::RectangleShape IntelligenceEntity::GetUI(int _i)
{
	return *shape_UI_elements[_i];
}

sf::Text IntelligenceEntity::GetName()
{
	return name;
}

float IntelligenceEntity::GetHealth()
{
	return stats->health;
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

void IntelligenceEntity::InitShapes()
{	
	//name
	name_font.loadFromFile("Font.ttf");
	name.setString("Cletus");
	name.setCharacterSize(25);
	name.setFont(name_font);
	name.setOutlineColor(sf::Color::Black);
	name.setOutlineThickness(1);
	name.setPosition(365, 145);

	//AI visual representation
	entity_shape.setSize(sf::Vector2f(50, 50));
	entity_shape.setOutlineColor(sf::Color::Black);
	entity_shape.setOutlineThickness(2);
	entity_shape.setFillColor(sf::Color::Yellow);
	entity_shape.setOrigin(25, 25);
	entity_shape.setPosition(400, 200);

	stats->pos_x = entity_shape.getPosition().x;
	stats->pos_y = entity_shape.getPosition().y;
	stats->target_x = stats->pos_x;
	stats->target_y = stats->pos_y;

	//UI
	int bar_height = 40;
	int bar_width = 10;

	health_UI.setSize(sf::Vector2f(bar_width, bar_height));
	health_UI.setFillColor(sf::Color(255, 0, 0, 255));
	health_UI.setPosition(380, 180);
	shape_UI_elements.push_back(&health_UI);

	hunger_UI.setSize(sf::Vector2f(bar_width, bar_height));
	hunger_UI.setFillColor(sf::Color(255, 102, 0, 255));
	hunger_UI.setPosition(395, 180);
	shape_UI_elements.push_back(&hunger_UI);

	thirst_UI.setSize(sf::Vector2f(bar_width, bar_height));
	thirst_UI.setFillColor(sf::Color(0, 0, 255, 255));
	thirst_UI.setPosition(410, 180);
	shape_UI_elements.push_back(&thirst_UI);

	health_outline.setSize(sf::Vector2f(bar_width, bar_height));
	health_outline.setOutlineColor(sf::Color::Black);
	health_outline.setOutlineThickness(2);
	health_outline.setFillColor(sf::Color::Transparent);
	health_outline.setPosition(380, 180);
	shape_UI_elements.push_back(&health_outline);

	hunger_outline.setSize(sf::Vector2f(bar_width, bar_height));
	hunger_outline.setOutlineColor(sf::Color::Black);
	hunger_outline.setOutlineThickness(2);
	hunger_outline.setFillColor(sf::Color::Transparent);
	hunger_outline.setPosition(395, 180);
	shape_UI_elements.push_back(&hunger_outline);

	thirst_outline.setSize(sf::Vector2f(bar_width, bar_height));
	thirst_outline.setOutlineColor(sf::Color::Black);
	thirst_outline.setOutlineThickness(2);
	thirst_outline.setFillColor(sf::Color::Transparent);
	thirst_outline.setPosition(410, 180);
	shape_UI_elements.push_back(&thirst_outline);	
}

void IntelligenceEntity::UpdateUI()
{
	//keep stats in range
	if (stats->food > 100)
	{
		stats->food = 100;
	}

	if (stats->thirst > 100)
	{
		stats->thirst = 100;
	}

	//update stat bars
	float perc = stats->food / 100;
	perc * 30.0f;
	hunger_UI.setScale(1, perc);

	if (stats->health > 0)
	{
		perc = stats->health / 100;
		perc * 30.0f;
		health_UI.setScale(1, perc);
	}

	perc = stats->thirst / 100;
	perc * 30.0f;
	thirst_UI.setScale(1, perc);
}

void IntelligenceEntity::Sight()
{
	//clear last update's nearby objects
	stats->nearby_objects.clear();

	//check which game objects are in range
	//add to vector
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
	Sight();

	//update shape position to recorded position
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
	//move all shapes together
	name.move(_offsetX, _offsetY);

	entity_shape.move(_offsetX, _offsetY);

	hunger_outline.move(_offsetX, _offsetY);
	hunger_UI.move(_offsetX, _offsetY);

	health_outline.move(_offsetX, _offsetY);
	health_UI.move(_offsetX, _offsetY);

	thirst_outline.move(_offsetX, _offsetY);
	thirst_UI.move(_offsetX, _offsetY);

	//update position
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
	//keep in range
	if (stats->target_x < 0)
	{
		stats->target_x = 0;
	}

	if (stats->target_x > 1475)
	{
		stats->target_x = 1475;
	}

	if (stats->target_y < 0)
	{
		stats->target_y = 0;
	}

	if (stats->target_y > 975)
	{
		stats->target_x = 975;
	}
}

void IntelligenceEntity::Update()
{
	UpdateUI();

	//if dead
	//kill entity shapes
	if (stats->health < 1)
	{
		stats->food = 0;
		stats->thirst = 0;

		UpdateUI();

		if (entity_shape.getFillColor() != sf::Color::Black)
		{
			entity_shape.setFillColor(sf::Color::Black);
		}
	}

	//otherwise execute behaviour
	else
	{
		Behaviour();
		BoundingBox();
	}
}





