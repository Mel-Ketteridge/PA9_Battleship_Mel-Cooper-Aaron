#include <SFML\Graphics.hpp>
#include "board.h"
#include <iostream>
#include "constants.h"
#include "computerBoard.h"
#include <stdlib.h>     //for using the function sleep

int main() {
	sf::RenderWindow window(sf::VideoMode(2000,950), "First Try");
	srand(time(NULL));
	Board playerBoard;
	ComputerBoard computerBoard;
	bool horizVert = false;
	int gameStatus = 0;
	//0 is Placing Carrier, 1 is playing Cruiser, 2 is placing submarine, 3 is Destroyer, 4 Patrol Boat

	sf::Vector2i cursorPos;
	sf::Vector2i mouseClickedPos;

	//This while loop is for placing the 
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
						playerBoard.setShip(mouseClickedPos, CRUSER, horizVert, gameStatus);
						horizVert = !horizVert;
					}
					if (gameStatus == 2) {
						playerBoard.setShip(mouseClickedPos, SUB, horizVert, gameStatus);
						horizVert = !horizVert;
					}
					if (gameStatus == 3) {
						playerBoard.setShip(mouseClickedPos, DESTROYER, horizVert, gameStatus);
						horizVert = !horizVert;
					}
					if (gameStatus == 4) {
						playerBoard.setShip(mouseClickedPos, PATROL, horizVert, gameStatus);
						horizVert = !horizVert;
					}

					//Check if confirm button has been pressed
					if (!playerBoard.checkConfirmClicked(mouseClickedPos, gameStatus))
						playerBoard.setRed();
				}
			}
		}
		
		playerBoard.hover(cursorPos);
		playerBoard.draw(window);
		computerBoard.draw(window);
		computerBoard.hover(cursorPos);
		window.display();

	}
	//Resetting game status so we can now place for the 
	gameStatus = 0;
	//This loop uses gameStatus to make random placements for the computer
	
	while (gameStatus < 5) {
		if (gameStatus == 0) {
			computerBoard.setRandomShip(CARRIER, horizVert, gameStatus);
		}
		if (gameStatus == 1) {
			computerBoard.setRandomShip(CRUSER, horizVert, gameStatus);
		}
		if (gameStatus == 2) {
			computerBoard.setRandomShip(SUB, horizVert, gameStatus);
		}
		if (gameStatus == 3) {
			computerBoard.setRandomShip(DESTROYER, horizVert, gameStatus);
		}
		if (gameStatus == 4) {
			computerBoard.setRandomShip(PATROL, horizVert, gameStatus);
		}
		gameStatus++;
	}



	//Play has placed ships, and computer has placed ships... next loop is for the game logic
	
	int turn = 0 , stopGame = 0;
	//I made the stopGame variable to 
	while (window.isOpen() && stopGame == 0) {
		if (turn == 0) { //The players turn
			//Player logic
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::MouseMoved) {
					cursorPos = sf::Mouse::getPosition(window);
				}

				if (event.type == sf::Event::MouseButtonPressed) {
					//Person has clicked...
					cursorPos = sf::Mouse::getPosition(window);
					if (event.mouseButton.button == sf::Mouse::Left) {
						mouseClickedPos = sf::Mouse::getPosition(window);
						//If the player hit an actual circle that hasn't already been hit
						if (computerBoard.playerHitBoard(mouseClickedPos)) {
							turn++;
						}
						
					}
				}
			}

			playerBoard.hover(cursorPos);
			playerBoard.draw(window);
			computerBoard.hover(cursorPos);
			computerBoard.findDestroyed();
			computerBoard.draw(window);
			window.display();
			
		}
		else if (turn == 1) { //The Computers turn
			//Computer logic
			playerBoard.computerHitBoard();
			turn--;
		}

		
	}
	
	/*
	while (window.isOpen()) {
		printf("HIT THE NEXT WHILE LOOP\n");
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
	*/
	return 0;
}