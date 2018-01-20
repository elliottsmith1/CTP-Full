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

	VirtualM virtual_machine;

	std::thread t1(ThreadVM, &virtual_machine);

	t1.detach();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) || (event.type == sf::Event::Closed))
			{
				window.close();
			}
		}

		int state = virtual_machine.GetState();

		printf("\nSTATE: %d\n", state);

		if (state == 1)
		{
			shape.setFillColor(sf::Color::Red);
			shape.move(-0.01f, 0.0f);
		}

		else if (state == 2)
		{
			shape.setFillColor(sf::Color::Blue);
			shape.move(0.01f, 0.0f);
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	//t1.join();

	return 0;
}

void ThreadVM(VirtualM* v_m)
{
	v_m->Machine();
}