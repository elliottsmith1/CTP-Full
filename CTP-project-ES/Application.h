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

	void Init();	//used to initialise all obects	
	void Update();	//game update
	void CreateVirtualMachines();	//create virtual machines
	void CleanUpVMachines();	//delete virtual machines when done
	void RunVMachines();	//update VMs


	//getters
	MapCreator* GetMapCreator();	
	sf::RectangleShape GetGameObject(int _i);
	sf::RectangleShape GetUI(int _i);
	sf::Text GetEntityName();
	int GetUISize();
	int GetGameObjectNum();

private:
	int num_enemies = 6; //number of enemies to spawn

	FileManager* file_manager;	//used to load FSMs
	IntelligenceEntity* entity;	//intelligence entity
	std::vector<Enemy*> enemies;	//enemies
	MapCreator* map_creator;	//creates map
	std::vector<sf::RectangleShape*> game_objects; //all game objects

	//FSM programs
	std::vector<float*> behaviours;
	//Virtual machines
	std::vector<VirtualM*> virtual_machines;
};

#pragma once
