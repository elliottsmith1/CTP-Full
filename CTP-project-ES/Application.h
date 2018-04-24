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
#include "Enemy.h"
#include "FileManager.h"

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
	sf::RectangleShape GetUI(int _i);
	sf::Text GetEntityName();
	int GetUISize();
	int GetGameObjectNum();

private:
	int num_enemies = 6;

	FileManager* file_manager;
	IntelligenceEntity* entity;
	std::vector<Enemy*> enemies;
	MapCreator* map_creator;
	std::vector<sf::RectangleShape*> game_objects;

	//FSM programs
	std::vector<float*> behaviours;
	//Virtual machines
	std::vector<VirtualM*> virtual_machines;
};

#pragma once
