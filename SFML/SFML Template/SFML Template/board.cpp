#include "board.h"

Board::Board():numOfCols(8),numOfRows(8),xPixals(1000),yPixals(950),pointRadius(15),seperationOfPoints(65),
xOffset(120),yOffset(160),buttonPosX(850),buttonPosY(200){

	//Initilize Random Things you use later
	lastClickedCircle.x = 0;
	lastClickedCircle.y = 0;
	carrier = 5; cruiser = 4; destroyer = 3; sub = 3; patrol = 2;

	//Set the background
	backgroundTexture.loadFromFile("background.png");
	background.setTexture(backgroundTexture);
	background.setPosition(0, 0);
	

	//Setup the Text
	timesNewRoman.loadFromFile("TarrgetLaserItalic-pzxR.otf");
	boardText[0].setFont(timesNewRoman);
	boardText[0].setPosition(100, 20);
	boardText[0].setFillColor(sf::Color::White);
	boardText[0].setCharacterSize(70);
	boardText[0].setString("Player Board");

	//Game Over Text
	gameOverText.setFont(timesNewRoman);
	gameOverText.setPosition(500, 400);
	gameOverText.setFillColor(sf::Color::Magenta);
	gameOverText.setCharacterSize(100); 

	//Bottom Text
	bottomText.setFont(timesNewRoman);
	bottomText.setPosition(50, 870);
	bottomText.setFillColor(sf::Color::White);
	bottomText.setStyle(sf::Style::Titlebar);
	bottomText.setCharacterSize(28);

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

	//Loading in ships, setting origin, texture, and rotation.
	//Carrier
	shipsTexture[0].loadFromFile("ShipCarrierHull.png"); 
	ships[0].setTexture(shipsTexture[0]);
	ships[0].setOrigin(39, 40);
	ships[0].setRotation(180);

	//Cruiser
	shipsTexture[1].loadFromFile("ShipCruiserHull.png"); 
	ships[1].setTexture(shipsTexture[1]);
	ships[1].setOrigin(33, 30);
	ships[1].setRotation(180);

	//Destroyer
	shipsTexture[2].loadFromFile("ShipDestroyerHull.png"); 
	ships[2].setTexture(shipsTexture[2]);
	ships[2].setOrigin(27, 25);
	ships[2].setRotation(180);
	 
	//Submarine
	shipsTexture[3].loadFromFile("ShipSubMarineHull.png");
	ships[3].setTexture(shipsTexture[3]);
	ships[3].setOrigin(33, 25);
	ships[3].setRotation(180);

	//Patrol
	shipsTexture[4].loadFromFile("ShipPatrolHull.png");
	ships[4].setTexture(shipsTexture[4]);
	ships[4].setOrigin(20, 40);
	ships[4].setRotation(180);
}

//Draw the board on the window
void Board::draw(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(boardText[0]); //Player Board
	window.draw(ships[0]);
	window.draw(ships[1]);
	window.draw(ships[2]);
	window.draw(ships[3]);
	window.draw(ships[4]);
	//window.draw(buttonSprites[0]); //Horizontal Button
	//window.draw(boardText[1]); //Horizontal Text
	//window.draw(buttonSprites[1]); //Vertical Button
	//window.draw(boardText[2]); //Vertical Text
	window.draw(buttonSprites[2]); //Confirm Button
	window.draw(boardText[3]); //Confirm Text

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
				if (!points[i][j].getClicked()) {
					points[i][j].setFillColor(sf::Color::Blue);
				}
				//prev = &points[i][j];
			}
		}
	}
}

//If you click on a tile make it blue, if you click on it again make it white
void Board::setRed() {
	sf::Vector2i spriteCenter;
	sf::FloatRect spriteBounds;
	//for (int i = 0; i < numOfCols; i++) {
	//	for (int j = 0; j < numOfRows; j++) {
	//
	//		//Find the center of the circle
	//		spriteBounds = points[i][j].getGlobalBounds();
	//		spriteCenter.x = spriteBounds.left + (spriteBounds.width / 2);
	//		spriteCenter.y = spriteBounds.top + (spriteBounds.height / 2);
	//
	//		//If the current cursorPosition is within the radius of the Point then turn it blue
	//		if (sqrt(pow((spriteCenter.x - (double)mouseClickedPos.x), 2) + pow((spriteCenter.y - (double)mouseClickedPos.y), 2))
	//			<= (double)pointRadius) {
	//			if (points[i][j].getClicked()) {
	//				points[i][j].setFillColor(sf::Color::Red);
	//				std::cout << "fuck";
	//			}
	//			
	//		}
	//	}
	//}
	//std::cout << lastClickedCircle.x << "  " <<  lastClickedCircle.y;
	points[lastClickedCircle.x][lastClickedCircle.y].setFillColor(sf::Color::Red);
	points[lastClickedCircle.x][lastClickedCircle.y].setClicked(true);

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
					lastClickedCircle.x = i; lastClickedCircle.y = j; //Store last clicked on sprite
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

	if (gameStatus == 0) { //Placing Carrier

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
	else if (gameStatus == 2) {

		if (!horizVert) {
			checkOrientation = ships[2].getGlobalBounds();
			if (checkOrientation.height > checkOrientation.width) {
				ships[2].setRotation(-90);
			}

			ships[2].setPosition(spriteCenter.x, spriteCenter.y);
		}

		if (horizVert) {
			checkOrientation = ships[2].getGlobalBounds();
			if (checkOrientation.height < checkOrientation.width) {
				ships[2].setRotation(180);
			}

			ships[2].setPosition(spriteCenter.x, spriteCenter.y);
		}
	}
	else if (gameStatus == 3) {

		if (!horizVert) {
			checkOrientation = ships[3].getGlobalBounds();
			if (checkOrientation.height > checkOrientation.width) {
				ships[3].setRotation(-90);
			}

			ships[3].setPosition(spriteCenter.x, spriteCenter.y);
		}

		if (horizVert) {
			checkOrientation = ships[3].getGlobalBounds();
			if (checkOrientation.height < checkOrientation.width) {
				ships[3].setRotation(180);
			}

			ships[3].setPosition(spriteCenter.x, spriteCenter.y);
		}
	}
	else if (gameStatus == 4) {

		if (!horizVert) {
			checkOrientation = ships[4].getGlobalBounds();
			if (checkOrientation.height > checkOrientation.width) {
				ships[4].setRotation(-90);
			}

			ships[4].setPosition(spriteCenter.x, spriteCenter.y);
		}

		if (horizVert) {
			checkOrientation = ships[4].getGlobalBounds();
			if (checkOrientation.height < checkOrientation.width) {
				ships[4].setRotation(180);
			}

			ships[4].setPosition(spriteCenter.x, spriteCenter.y);
		}
	}
}

bool Board::checkConfirmClicked(sf::Vector2i mouseClickedPos, int& gameStatus) {
	//Converting Vector2i to Vector2f
	sf::Vector2f mouseClickedFloat(mouseClickedPos.x, mouseClickedPos.y);
	sf::FloatRect bounds = buttonSprites[2].getGlobalBounds();
	sf::Vector2i spriteCenter;
	sf::FloatRect spriteBounds;
	//Checking if confirm has been pressed
	if (bounds.contains(mouseClickedFloat)) {
		//Confirm has been pressed
		std::vector<sf::Vector2i> pointVector;
		for (int i = 0; i < numOfCols; i++) {
			for (int j = 0; j < numOfRows; j++) {
				//Find the center of the circle
				spriteBounds = points[i][j].getGlobalBounds();
				spriteCenter.x = spriteBounds.left + (spriteBounds.width / 2);
				spriteCenter.y = spriteBounds.top + (spriteBounds.height / 2);

				//If the current cursorPosition is within the radius of the Point then turn it blue
				sf::FloatRect shipRect = ships[gameStatus].getGlobalBounds();
				if (shipRect.contains(spriteCenter.x, spriteCenter.y)) {
					//Current circle contains ship sprite
					printf("Entered if statement\n");
					sf::Vector2i tempPoint;
					tempPoint.x = j;
					tempPoint.y = i;
					pointVector.push_back(tempPoint);
					if (points[i][j].getIsOccupied()) {
						printf("getIsOccupied if statement entered");
						return false;
					} 
				}
			}
		}
		
		//See if any spots in pointVector are occupied
		return checkPointVector(pointVector, gameStatus);

		
	}
	return true;
}

bool Board::checkPointVector(std::vector<sf::Vector2i> pointVector, int& gameStatus) {
	int shipLength = 0;
	if (gameStatus == 0) {
		shipLength = 5;
	}
	if (gameStatus == 1) {
		shipLength = 4;
	}
	if (gameStatus == 2) {
		shipLength = 3;
	}
	if (gameStatus == 3) {
		shipLength = 3;
	}
	if (gameStatus == 4) {
		shipLength = 2;
	}
	
	int vectorSize = pointVector.size();
	printf("vectorSize = %d \n shipLength = %d", vectorSize, shipLength);
	if (vectorSize != shipLength ) { 
		printf("ERR: vectorSize != shipLength");
		return false;
	}
	else {
		for (int i = 0; i < shipLength; i++) {
			//printf("");
			points[pointVector[i].y][pointVector[i].x].setIsOccupied(true);
		}
		gameStatus++;
	}

	return true;
}

void Board::setBoardCircleShipStatus() {

	sf::FloatRect carrierBounds = ships[0].getGlobalBounds();
	sf::FloatRect cruiserBounds = ships[1].getGlobalBounds();
	sf::FloatRect destroyerBounds = ships[2].getGlobalBounds();
	sf::FloatRect subBounds = ships[3].getGlobalBounds();
	sf::FloatRect patrolBounds = ships[4].getGlobalBounds();

	sf::Vector2i spriteCenter;
	sf::FloatRect spriteBounds;
	for (int i = 0; i < numOfCols; i++) {
		for (int j = 0; j < numOfRows; j++) {
			
			//Find the center of the circle
			spriteBounds = points[i][j].getGlobalBounds();
			spriteCenter.x = spriteBounds.left + (spriteBounds.width / 2);
			spriteCenter.y = spriteBounds.top + (spriteBounds.height / 2);
			
			if (carrierBounds.contains(spriteCenter.x, spriteCenter.y))
				points[i][j].setShip(0);
			if (cruiserBounds.contains(spriteCenter.x, spriteCenter.y))
				points[i][j].setShip(1);
			if (destroyerBounds.contains(spriteCenter.x, spriteCenter.y))
				points[i][j].setShip(3);
			if (subBounds.contains(spriteCenter.x, spriteCenter.y))
				points[i][j].setShip(2);
			if (patrolBounds.contains(spriteCenter.x, spriteCenter.y))
				points[i][j].setShip(4);

		}
	}
}

bool Board::gameOver() {
	if (carrier == 0 && cruiser == 0 && destroyer == 0 && sub == 0 && patrol == 0) {
		return true;
	}
	return false;
}

bool Board::computerHitBoard() {
	int randomY = 0, randomX = 0;
	do {
		randomY = rand() % 8;
		randomX = rand() % 8;
	} while (points[randomY][randomX].getClicked());

	if (points[randomY][randomX].getIsOccupied()) {
		points[randomY][randomX].setFillColor(sf::Color::Red);
		points[randomY][randomX].setClicked(true);
		if (points[randomY][randomX].getShip() == 0)
			carrier--;
		if (points[randomY][randomX].getShip() == 1)
			cruiser--;
		if (points[randomY][randomX].getShip() == 2)
			sub--;
		if (points[randomY][randomX].getShip() == 3)
			destroyer--;
		if (points[randomY][randomX].getShip() == 4)
			patrol--;
		return true;
	}
	else {
		points[randomY][randomX].setFillColor(sf::Color::Green);
		points[randomY][randomX].setClicked(true);
		return true;
	}


}

void Board::setGameOverText(std::string text, sf::RenderWindow& window) {
	gameOverText.setString(text);
	window.draw(gameOverText);
}


void Board::setBottomText(std::string text, sf::RenderWindow& window) {
	bottomText.setString(text);
	window.draw(bottomText);
}