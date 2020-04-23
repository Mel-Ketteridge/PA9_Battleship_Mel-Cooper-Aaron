#include "board.h"

Board::Board():numOfCols(8),numOfRows(8),xPixals(1000),yPixals(950),pointRadius(40),seperationOfPoints(15),
xOffset(120),yOffset(160){

	//Set the background
	backgroundTexture.loadFromFile("background.png");
	background.setTexture(backgroundTexture);
	background.setPosition(0, 0);

	//Setup the Text
	timesNextRoman.loadFromFile("timesbd.ttf");
	boardText.setFont(timesNextRoman);
	boardText.setPosition(100, 20);
	boardText.setFillColor(sf::Color::Black);
	boardText.setCharacterSize(100);
	boardText.setString("Player Board");

	//Initilize all the circles at the correct positions
	for (int i = 0; i < numOfCols; i++) {
		for (int j = 0; j < numOfRows; j++) {
			points[i][j].setRadius(pointRadius);
			points[i][j].setPosition(((pointRadius * 2 + seperationOfPoints) * i) + xOffset,
				((pointRadius * 2 + seperationOfPoints) * j) + yOffset);
		}
	}

}

//Draw the board on the window
void Board::draw(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(boardText);
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
	for (int i = 0; i < numOfCols; i++) {
		for (int j = 0; j < numOfRows; j++) {
			points[i][j].setFillColor(sf::Color::White);
			spriteBounds = points[i][j].getGlobalBounds();
			//Find the center of the circle
			spriteCenter.x = spriteBounds.left + (spriteBounds.width / 2);
			spriteCenter.y = spriteBounds.top + (spriteBounds.height / 2);

			//If the current cursorPosition is within the radius of the Point then turn it blue
			if (sqrt(pow((spriteCenter.x - (double)cursorPos.x), 2) + pow((spriteCenter.y - (double)cursorPos.y), 2)) 
				<= (double) pointRadius) {
				points[i][j].setFillColor(sf::Color::Blue);
			}
		}
	}
}
