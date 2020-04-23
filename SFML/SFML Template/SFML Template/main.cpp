#include <SFML\Graphics.hpp>
#include "board.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1000,950), "First Try");

	Board playerBoard;

	sf::Vector2i cursorPos;
	while (window.isOpen()) {
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
		}

		//update
		window.clear();
		//Draw objects
		
		playerBoard.hover(cursorPos);
		playerBoard.draw(window);

		window.display();
	}

	return 0;
}