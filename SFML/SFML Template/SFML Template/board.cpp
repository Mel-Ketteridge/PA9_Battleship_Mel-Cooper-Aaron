#include "board.h"

Board::Board():numOfCols(8),numOfRows(8),xPixals(1000),yPixals(950),pointRadius(20),seperationOfPoints(55),
xOffset(120),yOffset(160),buttonPosX(850),buttonPosY(200){

	//Set the background
	backgroundTexture.loadFromFile("background.png");
	background.setTexture(backgroundTexture);
	background.setPosition(0, 0);

	//Setup the Text
	timesNewRoman.loadFromFile("timesbd.ttf");
	boardText.setFont(timesNewRoman);
	boardText.setPosition(100, 20);
	boardText.setFillColor(sf::Color::Black);
	boardText.setCharacterSize(100);
	boardText.setString("Player Board");

	//Set Button Size
	buttonSize.y = 40; buttonSize.x = 100;

	//Set Button Text
	horizontalText.setFont(timesNewRoman);
	horizontalText.setPosition(buttonPosX + 10, buttonPosY + 5);
	horizontalText.setFillColor(sf::Color::Black);
	horizontalText.setCharacterSize(15);
	horizontalText.setString("Horizontal");

	verticalText.setFont(timesNewRoman);
	verticalText.setPosition(buttonPosX + 10, buttonPosY + buttonSize.y + 25);
	verticalText.setFillColor(sf::Color::Black);
	verticalText.setCharacterSize(15);
	verticalText.setString("Vertical");

	//Set Button Sprits
	buttonTexture.loadFromFile("button.png");
	horizontal.setTexture(buttonTexture);
	horizontal.setScale(buttonSize);
	horizontal.setFillColor(sf::Color::White);
	horizontal.setPosition(buttonPosX, buttonPosY);

	vertical.setTexture(buttonTexture);
	vertical.setScale(buttonSize);
	vertical.setFillColor(sf::Color::White);
	vertical.setPosition(buttonPosX, buttonPosY + buttonSize.y + 20);

	//Initilize all the circles at the correct positions
	for (int i = 0; i < numOfCols; i++) {
		for (int j = 0; j < numOfRows; j++) {
			points[i][j].setRadius(pointRadius);
			points[i][j].setPosition(((pointRadius * 2 + seperationOfPoints) * i) + xOffset,
				((pointRadius * 2 + seperationOfPoints) * j) + yOffset);
		}
	}

	//Place the ships
	carrierTexture.loadFromFile("ShipCarrierHull.png");
	carrier.setTexture(carrierTexture);
	carrier.setRotation(-90);
}

//Draw the board on the window
void Board::draw(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(boardText);
	window.draw(carrier);
	window.draw(horizontal);
	window.draw(horizontalText);
	window.draw(vertical);
	window.draw(verticalText);
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

void Board::setShip(sf::Vector2i mouseClickedPos, sf::RenderWindow& window, int whichShip) {
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
					if (whichShip == 5) {
						carrier.setPosition(spriteCenter.x - pointRadius, spriteCenter.y + pointRadius);
					}
				}
				else {
					points[i][j].setFillColor(sf::Color::White);
					points[i][j].setClicked(false);
				}
			}
		}
	}
}
