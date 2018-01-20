#include <SFML/Graphics.hpp>

#include "VirtualM.h"

#include <memory>
#include <thread>
#include <string>
#include <iostream>

void ThreadVM(VirtualM* v_m);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "CTP Virtual Machine");

	sf::CircleShape shape(20.f);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(400, 200);

	//std::unique_ptr<VirtualM> virtual_machine = std::make_unique<VirtualM>();

	VirtualM virtual_machine;

	std::thread t1(ThreadVM, &virtual_machine);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	t1.join();

	return 0;
}

void ThreadVM(VirtualM* v_m)
{
	v_m->Machine();
}