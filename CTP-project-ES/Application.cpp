#include "Application.h"
#include "FSMBehaviour.h"

Application::Application()
{
	Init();
}

void Application::Init()
{
	//AI visual representation
	entity_shape.setSize(sf::Vector2f(40, 40));
	entity_shape.setOutlineColor(sf::Color::Black);
	entity_shape.setOutlineThickness(2);
	entity_shape.setFillColor(sf::Color::Yellow);
	entity_shape.setPosition(400, 200);	

	map_creator = new MapCreator;
	map_creator->SpawnMap();

	for (int i = 0; i < map_creator->GetMapSize(); i++)
	{
		game_objects.push_back(&map_creator->GetTile(i));
	}

	//game_objects.push_back(&entity_shape);

	behaviours.push_back(counting_FSM);
	behaviours.push_back(counting_FSM2);

	CreateVirtualMachines();
}

void Application::Update()
{
	if (map_creator->CheckFood(entity_shape))
	{
		map_creator->SpawnFood();
	}

	RunVMachines();
}

void Application::CreateVirtualMachines()
{
	//For every FSM, create a virtual machine to run it
	for (int i = 0; i < behaviours.size(); i++)
	{
		VirtualM* virtual_machine = new VirtualM;

		virtual_machine->SetID(i);

		virtual_machines.push_back(virtual_machine);

		virtual_machines[i]->Machine(behaviours[i]);

		//each VM runs on own thread
		//std::thread t1(&VirtualM::Machine, virtual_machines[i], behaviours[i]);

		//t1.detach();
	}
}

void Application::CleanUpVMachines()
{
	for (int i = 0; i < virtual_machines.size(); i++)
	{
		virtual_machines[i]->delVM(virtual_machines[i]->GetVM());
	}

	virtual_machines.clear();
	behaviours.clear();
}

void Application::RunVMachines()
{
	for (int i = 0; i < virtual_machines.size(); i++)
	{
		//virtual_machines[i]->Machine(behaviours[i]);

		int state = virtual_machines[i]->GetState();
		int id = virtual_machines[i]->GetID();

		printf("\n\nVM%d state: %d\n\n", id, state);

		switch (i)
		{
		//FSM 1
		case 0:
			switch (state)
			{
			case 1:
				entity_shape.move(-1.0f, 0.0f);
				break;
			case 2:
				entity_shape.move(1.0f, 0.0f);
				break;
			default:
				break;
			}
			break;

		//FSM 2
		case 1:
			switch (state)
			{
			case 1:
				if (entity_shape.getFillColor() != sf::Color::Red)
				{
					entity_shape.setFillColor(sf::Color::Red);
				}
				break;
			case 2:
				if (entity_shape.getFillColor() != sf::Color::Blue)
				{
					entity_shape.setFillColor(sf::Color::Blue);
				}
				break;
			case 3:
				if (entity_shape.getFillColor() != sf::Color::Magenta)
				{
					entity_shape.setFillColor(sf::Color::Magenta);
				}
				break;
			default:				
				break;
			}
		default:
			break;
		}
	}
}

MapCreator * Application::GetMapCreator()
{
	return map_creator;
}

sf::RectangleShape Application::GetGameObject(int _i)
{
	return *game_objects[_i];
}

int Application::GetGameObjectNum()
{
	return game_objects.size();
}


