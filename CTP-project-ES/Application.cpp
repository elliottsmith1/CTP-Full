#include "Application.h"
#include "FSMBehaviour.h"

Application::Application()
{
	Init();
}

void Application::Init()
{
	//loading files
	file_manager = new FileManager;

	//define which files to load
	float* target_movement = file_manager->LoadBehaviour("target_movement_FSM.txt");
	float* random_movement = file_manager->LoadBehaviour("random_movement_FSM.txt");
	float* hunger = file_manager->LoadBehaviour("hunger_FSM.txt");
	float* nearby_food = file_manager->LoadBehaviour("nearby_food_FSM.txt");
	float* thirst = file_manager->LoadBehaviour("thirst_FSM.txt");
	float* run = file_manager->LoadBehaviour("run_FSM.txt");

	//spawn entity
	entity = new IntelligenceEntity;	

	//spawn map
	map_creator = new MapCreator;
	map_creator->SpawnMap();

	//spawn enemies
	for (int i = 0; i < num_enemies; i++)
	{
		Enemy* enemy = new Enemy(entity);
		enemies.push_back(enemy);
	}	

	//update lists
	for (int i = 0; i < map_creator->GetMapSize(); i++)
	{
		game_objects.push_back(map_creator->GetTile(i));

		entity->GetStats()->game_objects.push_back(game_objects[i]);
	}		

	for (int i = 0; i < enemies.size(); i++)
	{
		game_objects.push_back(enemies[i]->GetEnemyShapes()[0]);
		entity->GetStats()->game_objects.push_back(enemies[i]->GetEnemyShapes()[0]);
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		game_objects.push_back(enemies[i]->GetEnemyShapes()[1]);
	}	

	game_objects.push_back(entity->GetEntityShape());	

	//FSMs
	behaviours.push_back(hunger);	//used to control hunger
	behaviours.push_back(target_movement);	//used to move to target position
	behaviours.push_back(random_movement);	//move randomly
	behaviours.push_back(nearby_food);	//seeks nearby food
	behaviours.push_back(thirst);	//handles thirst and water searching
	behaviours.push_back(run);	//avoids enemies

	CreateVirtualMachines();	//used to run FSMs
}

void Application::Update()
{
	//if entity still alive, update everthing
	if (entity->GetHealth() > 1)
	{
		RunVMachines();

		entity->Update();

		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->Update();
		}

		map_creator->Update();
	}
}

void Application::CreateVirtualMachines()
{
	//For every FSM, create a virtual machine to run it
	for (int i = 0; i < behaviours.size(); i++)
	{
		VirtualM* virtual_machine = new VirtualM;

		virtual_machine->SetStats(entity->GetStats());

		virtual_machine->SetID(i);

		virtual_machines.push_back(virtual_machine);

		virtual_machines[i]->Machine(behaviours[i]);

		//each VM runs on own thread *DEPRECATED*
		//std::thread t1(&VirtualM::Machine, virtual_machines[i], behaviours[i]);

		//t1.detach();
	}
}

void Application::CleanUpVMachines()
{
	//clean up VMs at end
	for (int i = 0; i < virtual_machines.size(); i++)
	{
		virtual_machines[i]->delVM(virtual_machines[i]->GetVM());
		delete virtual_machines[i];
	}

	virtual_machines.clear();
	behaviours.clear();
}

void Application::RunVMachines()
{
	//VM update
	for (int i = 0; i < virtual_machines.size(); i++)
	{
		//give VM most recent data
		virtual_machines[i]->SetStats(entity->GetStats());

		virtual_machines[i]->Run(virtual_machines[i]->GetVM());

		int state = virtual_machines[i]->GetState();
		int id = virtual_machines[i]->GetID();
	
		//update entity with new data
		entity->SetStats(virtual_machines[i]->GetStats());
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

sf::RectangleShape Application::GetUI(int _i)
{
	return entity->GetUI(_i);
}

sf::Text Application::GetEntityName()
{
	return entity->GetName();
}

int Application::GetUISize()
{
	return entity->GetUISize();
}

int Application::GetGameObjectNum()
{
	return game_objects.size();
}


