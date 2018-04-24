#include "Application.h"
#include "FSMBehaviour.h"

Application::Application()
{
	Init();
}

void Application::Init()
{
	file_manager = new FileManager;

	float* target_movement = file_manager->LoadBehaviour("target_movement_FSM.txt");
	float* random_movement = file_manager->LoadBehaviour("random_movement_FSM.txt");
	float* hunger = file_manager->LoadBehaviour("hunger_FSM.txt");
	float* nearby_food = file_manager->LoadBehaviour("nearby_food_FSM.txt");
	float* thirst = file_manager->LoadBehaviour("thirst_FSM.txt");
	float* run = file_manager->LoadBehaviour("run_FSM.txt");

	entity = new IntelligenceEntity;	

	map_creator = new MapCreator;
	map_creator->SpawnMap();

	for (int i = 0; i < num_enemies; i++)
	{
		Enemy* enemy = new Enemy(entity);
		enemies.push_back(enemy);
	}	

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

	behaviours.push_back(hunger);
	behaviours.push_back(target_movement);
	behaviours.push_back(random_movement);
	behaviours.push_back(nearby_food);
	behaviours.push_back(thirst);
	behaviours.push_back(run);

	CreateVirtualMachines();
}

void Application::Update()
{
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
		delete virtual_machines[i];
	}

	virtual_machines.clear();
	behaviours.clear();
}

void Application::RunVMachines()
{
	for (int i = 0; i < virtual_machines.size(); i++)
	{
		virtual_machines[i]->SetStats(entity->GetStats());

		//virtual_machines[i]->Machine(behaviours[i]);
		virtual_machines[i]->Run(virtual_machines[i]->GetVM());

		int state = virtual_machines[i]->GetState();
		int id = virtual_machines[i]->GetID();

		//printf("\n\nVM%d state: %d\n\n", id, state);

		//entity->InterpretFSM(id, state);		
		entity->SetStats(virtual_machines[i]->GetStats());
		//entity->Behaviour();
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


