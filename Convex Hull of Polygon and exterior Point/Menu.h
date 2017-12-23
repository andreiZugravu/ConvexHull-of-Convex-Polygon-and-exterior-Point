#pragma once

#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>

#define _WINDOW_WIDTH 1000
#define _WINDOW_HEIGHT 800

class Menu
{
	private:
		sf::Font font;

		sf::RectangleShape xButton;
		sf::Text xText;

		sf::RectangleShape yButton;
		sf::Text yText;

		sf::RectangleShape nButton;
		sf::Text nText;

		sf::Text generalText;

		sf::RectangleShape container;

		int state;

	public:
		Menu();
		~Menu();

		void draw(sf::RenderWindow & window);
		void handleEvent(sf::Event event, sf::RenderWindow & window);
};