#include <SFML/Graphics.hpp>

#include "VirtualM.h"
#include "FSMBehaviour.h"
#include "MapCreator.h"

#include <memory>
#include <vector>
#include <thread>
#include <string>
#include <iostream>

void ThreadVM(VirtualM* v_m, int* _code);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "CTP Virtual Machine");

	//AI visual representation
	sf::CircleShape shape(20.f);
	shape.setFillColor(sf::Color::Yellow);
	shape.setPosition(400, 200);

	MapCreator* map_creator = new MapCreator;

	map_creator->SpawnMap();

	//FSM programs
	std::vector<int*> behaviours;
	//Virtual machines
	std::vector<VirtualM*> virtual_machines;

	behaviours.push_back(counting_FSM);
	behaviours.push_back(counting_FSM2);	

	//For every FSM, create a virtual machine to run it
	for (int i = 0; i < behaviours.size(); i++)
	{
		VirtualM* virtual_machine = new VirtualM;

		virtual_machine->SetID(i);

		virtual_machines.push_back(virtual_machine);

		//each VM runs on own thread
		std::thread t1(&VirtualM::Machine, virtual_machines[i], behaviours[i]);

		t1.detach();
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) || (event.type == sf::Event::Closed))
			{
				window.close();

				for (int i = 0; i < virtual_machines.size(); i++)
				{
					virtual_machines[i]->delVM(virtual_machines[i]->GetVM());					
				}

				virtual_machines.clear();
				behaviours.clear();
			}
		}

		for (int i = 0; i < virtual_machines.size(); i++)
		{
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

					shape.move(-0.01f, 0.0f);
					break;

				case 2:

					shape.move(0.01f, 0.0f);
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

					if (shape.getFillColor() != sf::Color::Red)
					{
						shape.setFillColor(sf::Color::Red);
					}

					break;

				case 2:

					if (shape.getFillColor() != sf::Color::Blue)
					{
						shape.setFillColor(sf::Color::Blue);
					}

					break;

				case 3:

					if (shape.getFillColor() != sf::Color::Magenta)
					{
						shape.setFillColor(sf::Color::Magenta);
					}

					break;

				default:

					if (shape.getFillColor() != sf::Color::Yellow)
					{
						shape.setFillColor(sf::Color::Yellow);
					}
					break;
				}

			default:
				break;
			}
		}

		window.clear();		

		for (int i = 0; i < map_creator->GetMapSize(); i++)
		{
			window.draw(map_creator->GetTile(i));
		}

		window.draw(shape);

		window.display();
	}

	return 0;
}

void ThreadVM(VirtualM* v_m, int* _code)
{
	v_m->Machine(_code);
}