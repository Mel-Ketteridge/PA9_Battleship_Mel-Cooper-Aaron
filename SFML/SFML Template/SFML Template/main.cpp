#include <SFML\Graphics.hpp>
#include "board.h"
#include <iostream>
#include "constants.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1000,950), "First Try");

	Board playerBoard;

	sf::Vector2i cursorPos;
	sf::Vector2i mouseClickedPos;
	while (window.isOpen()) {
		//update
		window.clear();

		//Handle events 

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
			//If the mouse gets moved chnage the coursePos
			if (event.type == sf::Event::MouseMoved) {
				cursorPos = sf::Mouse::getPosition(window);
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					mouseClickedPos = sf::Mouse::getPosition(window);
					//playerBoard.clicked(mouseClickedPos);
					playerBoard.setShip(mouseClickedPos, window, CARRIER);
				}
			}
		}

		//Draw objects
		
		playerBoard.hover(cursorPos);
		playerBoard.draw(window);

		
		window.display();
	}

	return 0;
}