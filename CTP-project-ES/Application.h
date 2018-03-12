#include <SFML/Graphics.hpp>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>

#include "MapCreator.h"
#include "VirtualM.h"
#include "IntelligenceEntity.h"

class Application
{
public:
	Application();
	~Application() = default;

	void Init();
	void Update();
	void CreateVirtualMachines();
	void CleanUpVMachines();
	void RunVMachines();

	MapCreator* GetMapCreator();
	sf::RectangleShape GetGameObject(int _i);
	int GetGameObjectNum();

private:
	IntelligenceEntity* entity;
	MapCreator* map_creator;
	std::vector<sf::RectangleShape*> game_objects;

	//FSM programs
	std::vector<int*> behaviours;
	//Virtual machines
	std::vector<VirtualM*> virtual_machines;
};

#pragma once
