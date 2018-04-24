#include "Application.h"

#include <memory>
#include <vector>
#include <thread>
#include <string>
#include <iostream>

int main()
{
	Application* app = new Application;

	sf::RenderWindow window(sf::VideoMode(1400, 1000), "CTP Virtual Machine");	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				app->CleanUpVMachines();

				window.close();				
			}
		}

		window.clear(sf::Color::Black);

		app->Update();			

		for (int i = 0; i < app->GetGameObjectNum(); i++)
		{
			window.draw(app->GetGameObject(i));			
		}

		for (int i = 0; i < app->GetUISize(); i++)
		{
			window.draw(app->GetUI(i));
		}

		window.draw(app->GetEntityName());

		window.display();
	}

	return 0;
}
