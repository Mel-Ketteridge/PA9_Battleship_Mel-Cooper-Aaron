#include "computerBoard.h"

ComputerBoard::ComputerBoard() :numOfCols(8), numOfRows(8), xPixals(1000), yPixals(950), pointRadius(15), seperationOfPoints(65),
xOffset(1120), yOffset(160), buttonPosX(850), buttonPosY(200) {
	//Initilize Random Things you use later
	lastClickedCircle.x = 0;
	lastClickedCircle.y = 0;

	//Set the background
	backgroundTexture.loadFromFile("background.png");
	background.setTexture(backgroundTexture);
	background.setPosition(1000, 0);
	
	//Setup the Text
	timesNewRoman.loadFromFile("TarrgetLaserItalic-pzxR.otf");
	boardText[0].setFont(timesNewRoman);
	boardText[0].setPosition(1100, 20);
	boardText[0].setFillColor(sf::Color::White);
	boardText[0].setCharacterSize(70);
	boardText[0].setString("Computer Board");

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

	//Set Button Sprites
	buttonTexture.loadFromFile("button2.png");
	buttonSprites[0].setTexture(buttonTexture);
	buttonSprites[0].setPosition(buttonPosX, buttonPosY);

	buttonSprites[1].setTexture(buttonTexture);
	buttonSprites[1].setPosition(buttonPosX, buttonPosY + buttonSize.y);

	buttonSprites[2].setTexture(buttonTexture);
	buttonSprites[2].setPosition(buttonPosX, buttonPosY + buttonSize.y * 2);
	printf("numOfCols = %d \n", numOfCols);
	printf("numOfRows = %d \n", numOfRows);

	//Initilize all the circles at the correct positions
	for (int i = 0; i < numOfCols; i++) {
		for (int j = 0; j < numOfRows; j++) {
			points[i][j].setRadius(pointRadius);
			points[i][j].setPosition(((pointRadius * 2 + seperationOfPoints) * i) + xOffset ,
				((pointRadius * 2 + seperationOfPoints) * j) + yOffset);
		}
	}
}


void ComputerBoard::draw(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(boardText[0]); //Player Board
	//window.draw(ships[0]);
	//window.draw(ships[1]);
	//window.draw(ships[2]);
	//window.draw(ships[3]);
	//window.draw(ships[4]);
	//window.draw(buttonSprites[0]); //Horizontal Button
	//window.draw(boardText[1]); //Horizontal Text
	//window.draw(buttonSprites[1]); //Vertical Button
	//window.draw(boardText[2]); //Vertical Text
	//window.draw(buttonSprites[2]); //Confirm Button
	//window.draw(boardText[3]); //Confirm Text
	printf("numOfCols = %d \n", numOfCols);
	printf("numOfRows = %d \n", numOfRows);
	for (int i = 0; i < numOfCols; i++) {
		for (int j = 0; j < numOfRows; j++) {
			window.draw(points[i][j]);
			//printf("X = %d , Y = %d ",points[i][j].getPosition().x, points[i][j].getPosition().y);
		}
	}

}

void ComputerBoard::hover(sf::Vector2i cursorPos) {

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
				<= (double)pointRadius) {
				if (!points[i][j].getClicked()) {
					points[i][j].setFillColor(sf::Color::Blue);
				}
				//prev = &points[i][j];
			}
		}
	}
}

void ComputerBoard::setRandomShip(int shipSize, bool horiz_vert, int& gameStatus) {
	//srand(time(NULL));
	int response = (rand() % 2) + 1;
	if (response == 1) { //Player chose horizontally
		//printf("placing HORIZONTALLY \n");
		sf::Vector2i newPoint = { 0,0 };
		bool isOccupied;
		int withinBounds;
		do {
			newPoint.x = rand() % (8 - shipSize);
			newPoint.y = rand() % (8 - shipSize);
			//printf("newPOINT.x = %d", newPoint.x);
			//printf("newPOINT.y = %d", newPoint.y);
			isOccupied = checkIfOccupied(newPoint.x, newPoint.y, shipSize, response);
		} while (!(isOccupied == true));
		placeShip(newPoint, shipSize, response);
	}
	else if (response == 2) { //Player chose vertically
		//printf("placing HORIZONTALLY \n");
		sf::Vector2i newPoint = { 0,0 };
		int isOccupied;
		int withinBounds;
		do {
			newPoint.x = rand() % (8 - shipSize);
			newPoint.y = rand() % (8 - shipSize);
			//printf("newPOINT.x = %d", newPoint.x);
			//printf("newPOINT.y = %d", newPoint.y);
			isOccupied = checkIfOccupied(newPoint.x, newPoint.y, shipSize, response);
		} while (!(isOccupied == true));
		placeShip(newPoint, shipSize, response);
	}
};

bool ComputerBoard::checkIfOccupied(int x, int y, int shipLength, int direction) {
	if (direction == 1) { //Ship is placed horizontally
		for (int i = x; i < x + shipLength; i++) {
			//printf("Checking if occupied at %d , %d \n", i, y);
			if (points[y][i].getIsOccupied() == true) {
				//printf("Found occupied at %d , %d \n", i, y);
				return false;
			}
		}
	}
	else if (direction == 2) { //Ship is placed vertically
		for (int i = y; i < y + shipLength; i++) {
			if (points[i][x].getIsOccupied() == true) {
				//printf("Found occupied at %d , %d \n", i, y);
				return false;
			}
		}
	}
	return true;
}

void ComputerBoard::placeShip(sf::Vector2i point, int shipLength, int direction) {
	if (direction == 1) { //Ship is placed horizontally
		for (int i = point.x; i < point.x + shipLength; i++) {
			//printf("PLACING AT %d , %d", i, point.y);
			points[point.y][i].setFillColor(sf::Color::Black);
			points[point.y][i].setIsOccupied(true);
			points[point.y][i].setClicked(true);
		}
	}
	else if (direction == 2) { //Ship is placed vertically
		for (int i = point.y; i < point.y + shipLength; i++) {
			//printf("PLACING AT %d , %d", i, point.y);
			points[i][point.x].setFillColor(sf::Color::Black);
			points[i][point.x].setIsOccupied(true);
			points[i][point.x].setClicked(true);
		}
	}
}