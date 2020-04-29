#include "computerBoard.h"

ComputerBoard::ComputerBoard() :numOfCols(8), numOfRows(8), xPixals(1000), yPixals(950), pointRadius(1015), seperationOfPoints(65),
xOffset(1120), yOffset(1160), buttonPosX(850), buttonPosY(200) {
	//Initilize Random Things you use later
	lastClickedCircle.x = 0;
	lastClickedCircle.y = 0;

	//Set the background
	backgroundTexture.loadFromFile("background.png");
	background.setTexture(backgroundTexture);
	background.setPosition(1000, 0);
	
	//Setup the Text
	timesNewRoman.loadFromFile("timesbd.ttf");
	boardText[0].setFont(timesNewRoman);
	boardText[0].setPosition(100, 20);
	boardText[0].setFillColor(sf::Color::Black);
	boardText[0].setCharacterSize(100);
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
			points[i][j].setPosition(((pointRadius * 2 + seperationOfPoints) * i) + xOffset + 1000,
				((pointRadius * 2 + seperationOfPoints) * j) + yOffset + 1000);
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