#include "Menu.h"
#include <iostream>
#include "ResourceManager.h"

extern ResourceManager * instance;

Menu::Menu()
{
	static int counter = 0;
	state = 0;

	if (!font.loadFromFile("Crimson-Bold.otf"))
	{
		//handle error
		std::cout << "Crimson-Bold.otf font failed to load!\n";
	}

	xText.setFont(font);
	yText.setFont(font);

	nButton.setPosition(sf::Vector2f(_WINDOW_WIDTH / 3 + 90.f, 100.f));
	nButton.setSize(sf::Vector2f(150.f, 100.f));
	nButton.setFillColor(sf::Color::White);
	
	nText.setPosition(nButton.getPosition().x + 20.f, nButton.getPosition().y + 30.f);
	nText.setCharacterSize(30);
	nText.setFont(font);
	nText.setFillColor(sf::Color::Black);
	nText.setString("n = ");

	container.setPosition(sf::Vector2f(0.f, 0.f));
	container.setSize(sf::Vector2f(_WINDOW_WIDTH, _WINDOW_HEIGHT));
	container.setFillColor(sf::Color::Color(45, 111, 216, 155)); //set a rgba color

	generalText.setPosition(sf::Vector2f(_WINDOW_WIDTH / 3, 0.f));
	generalText.setCharacterSize(24);
	generalText.setFont(font);
	generalText.setFillColor(sf::Color::Black);
	generalText.setString("Welcome! Enter your data to continue!\n");
}


Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow & window)
{
	window.draw(container);

	window.draw(xButton);
	window.draw(xText);

	window.draw(yButton);
	window.draw(yText);

	window.draw(nButton);
	window.draw(nText);
	
	window.draw(generalText);
}

void Menu::handleEvent(sf::Event event, sf::RenderWindow & window)
{
	extern int counter;
	switch (event.type)
	{
		case sf::Event::KeyPressed :
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			else
			{
				switch (state)
				{
					case 0 :
						//retrieve n
						//0 = 26, 9 - 35
						char numbers[36];
						for (int i = 0; i < 10; i++)
							numbers[i + 26] = '0' + i;
						
						if (event.key.code == sf::Keyboard::BackSpace)
						{
							if (nText.getString().getSize() > 4)
								nText.setString(nText.getString().substring(0, nText.getString().getSize() - 1));
						}
						else if (event.key.code == sf::Keyboard::Return)
						{
							//calculate n
							state++; //move to next state
							//eliminate button. don't overcomplicate the draw function
							nButton.setPosition(sf::Vector2f(0.f, 0.f));
							nButton.setSize(sf::Vector2f(0.f, 0.f));
							nButton.setFillColor(container.getFillColor());
							//eliminate the text for the button
							nText.setPosition(nButton.getPosition());
							nText.setCharacterSize(0);
							nText.setFillColor(container.getFillColor());
							nText.setString("");

							//add button for x and y
							xButton.setPosition(sf::Vector2f(100.f, 100.f));
							xButton.setSize(sf::Vector2f(150.f, 100.f));
							xButton.setFillColor(sf::Color::White);

							yButton.setPosition(sf::Vector2f(100.f, 250.f));
							yButton.setSize(sf::Vector2f(150.f, 100.f));
							yButton.setFillColor(sf::Color::White);
							//add text for x and y
							xText.setPosition(xButton.getPosition().x + 30.f, xButton.getPosition().y + 30.f);
							xText.setCharacterSize(24);
							xText.setFillColor(sf::Color::Black);
							xText.setString("x = ");

							yText.setPosition(yButton.getPosition().x + 30.f, yButton.getPosition().y + 30.f);
							yText.setCharacterSize(24);
							yText.setFillColor(sf::Color::Black);
							yText.setString("y = ");

						}
						else
							nText.setString(nText.getString() + numbers[event.key.code]);

						break;

					case 1 :
						//retrieve polygon points
						if (counter < 1)
						{

						}
						break;

					case 2 :
						//retrieve exterior point

					default :
						break;
				}
			}

			break;

		case sf::Event::Closed :
			window.close();
			break;

		default :
			break;
	}
}