#include "board.h"

Board::Board():numOfCols(8),numOfRows(8),xPixals(1000),yPixals(950),pointRadius(15),seperationOfPoints(65),
xOffset(120),yOffset(160),buttonPosX(850),buttonPosY(200){

	//Set the background
	backgroundTexture.loadFromFile("background.png");
	background.setTexture(backgroundTexture);
	background.setPosition(0, 0);

	//Setup the Text
	timesNewRoman.loadFromFile("timesbd.ttf");
	boardText[0].setFont(timesNewRoman);
	boardText[0].setPosition(100, 20);
	boardText[0].setFillColor(sf::Color::Black);
	boardText[0].setCharacterSize(100);
	boardText[0].setString("Player Board");

	//Set Button Size
	buttonSize.y = 75; buttonSize.x = 150;

	//Set Button Text
	boardText[1].setFont(timesNewRoman);
	boardText[1].setPosition(buttonPosX + 10, buttonPosY + 20);
	boardText[1].setFillColor(sf::Color::Black);
	boardText[1].setCharacterSize(20);
	boardText[1].setString("Horizontal");

	boardText[2].setFont(timesNewRoman);
	boardText[2].setPosition(buttonPosX + 10, buttonPosY + buttonSize.y + 20);
	boardText[2].setFillColor(sf::Color::Black);
	boardText[2].setCharacterSize(20);
	boardText[2].setString("Vertical");

	boardText[3].setFont(timesNewRoman);
	boardText[3].setPosition(buttonPosX + 10, buttonPosY + buttonSize.y * 2 + 20);
	boardText[3].setFillColor(sf::Color::Black);
	boardText[3].setCharacterSize(20);
	boardText[3].setString("Confirm");

	//Set Button Sprits
	buttonTexture.loadFromFile("button2.png");
	buttonSprites[0].setTexture(buttonTexture);
	buttonSprites[0].setPosition(buttonPosX, buttonPosY);

	buttonSprites[1].setTexture(buttonTexture);
	buttonSprites[1].setPosition(buttonPosX, buttonPosY + buttonSize.y);

	buttonSprites[2].setTexture(buttonTexture);
	buttonSprites[2].setPosition(buttonPosX, buttonPosY + buttonSize.y * 2);

	//Initilize all the circles at the correct positions
	for (int i = 0; i < numOfCols; i++) {
		for (int j = 0; j < numOfRows; j++) {
			points[i][j].setRadius(pointRadius);
			points[i][j].setPosition(((pointRadius * 2 + seperationOfPoints) * i) + xOffset,
				((pointRadius * 2 + seperationOfPoints) * j) + yOffset);
		}
	}

	//Place the ships
	shipsTexture[0].loadFromFile("ShipCarrierHull.png");
	ships[0].setTexture(shipsTexture[0]);
	ships[0].setOrigin(39, 40);
	ships[0].setRotation(180);

	shipsTexture[1].loadFromFile("ShipCruiserHull.png");
	ships[1].setTexture(shipsTexture[1]);
	ships[1].setOrigin(33, 30);
	ships[1].setRotation(180);

}

//Draw the board on the window
void Board::draw(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(boardText[0]); //Player Board
	window.draw(ships[0]);
	window.draw(ships[1]);
	window.draw(buttonSprites[0]); //Horizontal Button
	window.draw(boardText[1]); //Horizontal Text
	window.draw(buttonSprites[1]); //Vertical Button
	window.draw(boardText[2]); //Vertical Text
	window.draw(buttonSprites[2]); //Vertical Button
	window.draw(boardText[3]); //Vertical Text

	for (int i = 0; i < numOfCols; i++) {
		for (int j = 0; j < numOfRows; j++) {
			window.draw(points[i][j]);
		}
	}
}

//Detect when the mouse hovers over a circle
void Board::hover(sf::Vector2i cursorPos) {

	sf::Vector2i spriteCenter;
	sf::FloatRect spriteBounds;
	//static boardCirles* prev = nullptr;
	for (int i = 0; i < numOfCols; i++) {
		for (int j = 0; j < numOfRows; j++) {
			//Make sure the previous tile that was hovered over is Blue
			if (!points[i][j].getClicked()) {
				points[i][j].setFillColor(sf::Color::White);
			}

			//Find the center of the circle
			spriteBounds = points[i][j].getGlobalBounds();
			spriteCenter.x = spriteBounds.left + (spriteBounds.width / 2);
			spriteCenter.y = spriteBounds.top + (spriteBounds.height / 2);

			//If the current cursorPosition is within the radius of the Point then turn it blue
			if (sqrt(pow((spriteCenter.x - (double)cursorPos.x), 2) + pow((spriteCenter.y - (double)cursorPos.y), 2)) 
				<= (double) pointRadius) {
				points[i][j].setFillColor(sf::Color::Blue);
				//prev = &points[i][j];
			}
		}
	}
}

//If you click on a tile make it blue, if you click on it again make it white
void Board::clicked(sf::Vector2i mouseClickedPos) {
	sf::Vector2i spriteCenter;
	sf::FloatRect spriteBounds;
	for (int i = 0; i < numOfCols; i++) {
		for (int j = 0; j < numOfRows; j++) {

			//Find the center of the circle
			spriteBounds = points[i][j].getGlobalBounds();
			spriteCenter.x = spriteBounds.left + (spriteBounds.width / 2);
			spriteCenter.y = spriteBounds.top + (spriteBounds.height / 2);

			//If the current cursorPosition is within the radius of the Point then turn it blue
			if (sqrt(pow((spriteCenter.x - (double)mouseClickedPos.x), 2) + pow((spriteCenter.y - (double)mouseClickedPos.y), 2))
				<= (double)pointRadius) {
				if (!points[i][j].getClicked()) {
					points[i][j].setFillColor(sf::Color::Blue);
					points[i][j].setClicked(true);
				}
				else {
					points[i][j].setFillColor(sf::Color::White);
					points[i][j].setClicked(false);
				}
			}
		}
	}
}

void Board::setShip(sf::Vector2i mouseClickedPos, int shipSize, bool horizVert, int &gameStatus) {

	sf::Vector2i spriteCenter;
	sf::FloatRect spriteBounds;

	for (int i = 0; i < numOfCols; i++) {
		for (int j = 0; j < numOfRows; j++) {

			if (points[i][j].getClicked()) {
				points[i][j].setFillColor(sf::Color::White);
				points[i][j].setClicked(false);
			}

			//Find the center of the circle
			spriteBounds = points[i][j].getGlobalBounds();
			spriteCenter.x = spriteBounds.left + (spriteBounds.width / 2);
			spriteCenter.y = spriteBounds.top + (spriteBounds.height / 2);

			//If the current cursorPosition is within the radius of the Point then turn it blue
			if (sqrt(pow((spriteCenter.x - (double)mouseClickedPos.x), 2) + pow((spriteCenter.y - (double)mouseClickedPos.y), 2))
				<= (double)pointRadius) {
				if (!points[i][j].getClicked()) {
					points[i][j].setFillColor(sf::Color::Blue);
					points[i][j].setClicked(true);
					placeShip(spriteCenter, shipSize, horizVert, gameStatus);
				}
				else {
					//points[i][j].setFillColor(sf::Color::White);
					//points[i][j].setClicked(false);
				}
			}
		}
	}
}

//False be Horizontal True be Vertical
void Board::placeShip(sf::Vector2i spriteCenter, int shipSize, bool horizVert, int& gameStatus) {
	sf::FloatRect checkOrientation;

	if (gameStatus == 0) {

		if (!horizVert) {
			checkOrientation = ships[0].getGlobalBounds();
			if (checkOrientation.height > checkOrientation.width) {
				ships[0].setRotation(-90);
			}

			ships[0].setPosition(spriteCenter.x, spriteCenter.y);
		}

		if (horizVert) {
			checkOrientation = ships[0].getGlobalBounds();
			if (checkOrientation.height < checkOrientation.width) {
				ships[0].setRotation(180);
			}

			ships[0].setPosition(spriteCenter.x, spriteCenter.y);
		}
	}
	else if (gameStatus == 1) {

		if (!horizVert) {
			checkOrientation = ships[1].getGlobalBounds();
			if (checkOrientation.height > checkOrientation.width) {
				ships[1].setRotation(-90);
			}

			ships[1].setPosition(spriteCenter.x, spriteCenter.y);
		}

		if (horizVert) {
			checkOrientation = ships[1].getGlobalBounds();
			if (checkOrientation.height < checkOrientation.width) {
				ships[1].setRotation(180);
			}

			ships[1].setPosition(spriteCenter.x, spriteCenter.y);
		}
	}
}
