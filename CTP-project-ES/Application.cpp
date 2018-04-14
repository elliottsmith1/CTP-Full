#include "Application.h"
#include "FSMBehaviour.h"

Application::Application()
{
	Init();
}

void Application::Init()
{
	entity = new IntelligenceEntity;

	map_creator = new MapCreator;
	map_creator->SpawnMap();

	for (int i = 0; i < map_creator->GetMapSize(); i++)
	{
		game_objects.push_back(map_creator->GetTile(i));

		entity->GetStats()->map_tiles.push_back(game_objects[i]);
	}

	//game_objects.push_back(entity->GetView());
	game_objects.push_back(entity->GetEntity());
	

	//behaviours.push_back(counting_FSM);
	//behaviours.push_back(counting_FSM2);
	behaviours.push_back(hunger_FSM);
	behaviours.push_back(aquire_food_FSM);

	CreateVirtualMachines();
}

void Application::Update()
{
	RunVMachines();

	entity->Update();

	map_creator->Update();
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

		printf("\n\nVM%d state: %d\n\n", id, state);

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

int Application::GetGameObjectNum()
{
	return game_objects.size();
}

