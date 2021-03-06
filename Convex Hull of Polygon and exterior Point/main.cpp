#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "ResourceManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(_WINDOW_WIDTH, _WINDOW_HEIGHT), "SFML works!");
	Menu menu;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			menu.handleEvent(event, window);
		}

		window.clear();
		menu.draw(window);
		window.display();
	}

	ResourceManager::getInstance()->freeResources();

	return 0;
}