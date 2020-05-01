#ifndef BOARD
#define BOARD

#include <SFML\Graphics.hpp>
#include <math.h>
#include <iostream>
#include "boardCircles.h"
#include "constants.h"
#include <vector>

class Board {
private:
	sf::Texture backgroundTexture;
	sf::Texture shipsTexture[5];
	sf::Texture buttonTexture;
	sf::Sprite background;
	sf::Sprite buttonSprites[3];
	sf::Vector2f buttonSize;
	sf::Vector2i lastClickedCircle;
	sf::Sprite ships[5];
	boardCirles points[8][8];
	sf::Text boardText[4];
	sf::Font timesNewRoman;
	int carrier, cruiser, destroyer, sub, patrol; 
	const int numOfCols;
	const int numOfRows;
	const int xPixals;
	const int yPixals;
	const int pointRadius;
	const int seperationOfPoints;
	const int xOffset;
	const int yOffset;
	const int buttonPosX;
	const int buttonPosY;
	bool areShipsSet;

public:
	Board();
	void draw(sf::RenderWindow& window);
	void hover(sf::Vector2i cursorPos);
	void setRed();
	void setShip(sf::Vector2i mouseClickedPos, int shipSize, bool horiz_vert, int &gameStatus);
	void placeShip(sf::Vector2i spriteCenter, int shipSize, bool horizVert, int& gameStatus);
	bool checkConfirmClicked(sf::Vector2i spriteCenter, int& gameStatus);
	bool checkPointVector(std::vector<sf::Vector2i> pointVector, int& gameStatus);
	void setBoardCircleShipStatus();
	bool computerHitBoard();
};





#endif