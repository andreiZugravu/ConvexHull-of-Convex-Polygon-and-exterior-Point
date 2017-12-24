#pragma once

#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>

#define _WINDOW_WIDTH 1000
#define _WINDOW_HEIGHT 800

#define _MAX_X_VALUE 20
#define _MAX_Y_VALUE 20

#define halfLen 2

#define jump 5

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

		sf::Vertex OX[2];
		sf::Vertex OY[2];

		sf::Vertex OX_points[(_WINDOW_WIDTH / _MAX_X_VALUE) * 2][2];
		sf::Vertex OY_points[(_WINDOW_HEIGHT / _MAX_Y_VALUE) * 2][2];

		sf::Text OX_points_text[(_WINDOW_WIDTH / _MAX_X_VALUE) * 2];
		sf::Text OY_points_text[(_WINDOW_HEIGHT / _MAX_Y_VALUE) * 2];

	public:
		Menu();
		~Menu();

		void draw(sf::RenderWindow & window);
		void handleEvent(sf::Event event, sf::RenderWindow & window);
};