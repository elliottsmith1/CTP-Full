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

void IntelligenceEntity::SetFoodInSight(bool _sight)
{
	food_in_sight = _sight;
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
		//FSM 1
		//case 0:
		//	switch (_state)
		//	{
		//	case 2:			
		//		switch (random_num)
		//		{
		//		case 0:
		//			MoveEntity(speed, 0);
		//			break;
		//		case 1:
		//			MoveEntity(-speed, 0);
		//			break;
		//		case 2:
		//			MoveEntity(0, speed);
		//			break;
		//		case 3:
		//			MoveEntity(0, -speed);
		//			break;
		//		}			
		//		break;
		//	case 1:
		//		if (food_in_sight)
		//		{
		//			if (food_pos.x > entity_shape.getPosition().x)
		//				MoveEntity(speed, 0);

		//			if (food_pos.x < entity_shape.getPosition().x)
		//				MoveEntity(-speed, 0);

		//			if (food_pos.y > entity_shape.getPosition().y)
		//				MoveEntity(0, speed);

		//			if (food_pos.y < entity_shape.getPosition().y)
		//				MoveEntity(0, -speed);
		//			return;
		//		}
		//		break;
		//	default:
		//		break;
		//	}
		//	break;

		////FSM 2
		//case 1:
		//	switch (_state)
		//	{
		//	case 1:
		//		if (entity_shape.getFillColor() != sf::Color::Red)
		//		{
		//			entity_shape.setFillColor(sf::Color::Red);
		//		}
		//		break;
		//	case 2:
		//		if (entity_shape.getFillColor() != sf::Color::Blue)
		//		{
		//			entity_shape.setFillColor(sf::Color::Blue);
		//		}
		//		break;
		//	case 3:
		//		if (entity_shape.getFillColor() != sf::Color::Magenta)
		//		{
		//			entity_shape.setFillColor(sf::Color::Magenta);
		//		}
		//		break;
		//	default:
		//		break;
		//	}
		//default:
		//	break;
		//}
			//FSM 3
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
}



