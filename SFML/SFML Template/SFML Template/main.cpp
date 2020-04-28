#include <SFML\Graphics.hpp>
#include "board.h"
#include <iostream>
#include "constants.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1000,950), "First Try");

	Board playerBoard;
	bool horizVert = false;
	int gameStatus = 0;
	//0 is Placing Carrier, 1 is playing Cruiser, 2 is placing submarine, 3 is Destroyer, 4 Patrol Boat

	sf::Vector2i cursorPos;
	sf::Vector2i mouseClickedPos;

	while (window.isOpen() && gameStatus < 5) {

		window.clear();

		sf::Event event;
		while (window.pollEvent(event)){

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseMoved) {
				cursorPos = sf::Mouse::getPosition(window);
			}

			if (event.type == sf::Event::MouseButtonPressed) {

				if (event.mouseButton.button == sf::Mouse::Left) {
					mouseClickedPos = sf::Mouse::getPosition(window);
					if (gameStatus == 0) {
						playerBoard.setShip(mouseClickedPos, CARRIER, horizVert, gameStatus);
						horizVert = !horizVert;
					}
					if (gameStatus == 1) {
						playerBoard.setShip(mouseClickedPos, DESTROYER, horizVert, gameStatus);
						horizVert = !horizVert;
					}
					if (gameStatus == 2) {
						playerBoard.setShip(mouseClickedPos, SUB, horizVert, gameStatus);
						horizVert = !horizVert;
					}
					if (gameStatus == 3) {
						playerBoard.setShip(mouseClickedPos, CRUSER, horizVert, gameStatus);
						horizVert = !horizVert;
					}
					if (gameStatus == 4) {
						playerBoard.setShip(mouseClickedPos, PATROL, horizVert, gameStatus);
						horizVert = !horizVert;
					}

					//Check if confirm button has been pressed
					
					if (!playerBoard.checkConfirmClicked(mouseClickedPos, gameStatus)) {
						playerBoard.clicked(mouseClickedPos);
					};
						
					
				}
			}
		}

		playerBoard.hover(cursorPos);
		playerBoard.draw(window);

		window.display();

	}

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

		}

		//Draw objects
		playerBoard.hover(cursorPos);
		playerBoard.draw(window);

		
		window.display();
	}

	return 0;
}