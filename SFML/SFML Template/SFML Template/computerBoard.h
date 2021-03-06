#ifndef COMPUTERBOARD
#define COMPUTERBOARD

#include <SFML\Graphics.hpp>
#include <math.h>
#include <iostream>
#include "boardCircles.h"
#include "constants.h"
#include <vector>

class ComputerBoard {
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
	sf::Text shipDestroyed;
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
	ComputerBoard();
	void draw(sf::RenderWindow& window);
	void hover(sf::Vector2i cursorPos);
	//void setRed();
	void setRandomShip(int shipSize, bool horiz_vert, int& gameStatus);
	bool checkIfOccupied(int x, int y, int shipLength, int direction);
	void placeShip(sf::Vector2i point, int shipLength, int direction, int gameStatus);
	bool playerHitBoard(sf::Vector2i cursorPos);
	bool findDestroyed();
	bool gameOver();
	//void placeShip(sf::Vector2i spriteCenter, int shipSize, bool horizVert, int& gameStatus);
	//bool checkConfirmClicked(sf::Vector2i spriteCenter, int& gameStatus);
	//bool checkPointVector(std::vector<sf::Vector2i> pointVector, int& gameStatus);
};



#endif