#ifndef BOARD
#define BOARD

#include <SFML\Graphics.hpp>
#include <math.h>
#include <iostream>
#include "boardCircles.h"
#include "constants.h"

class Board {
private:
	sf::Texture backgroundTexture;
	sf::Texture carrierTexture;
	sf::Texture buttonTexture;
	sf::Sprite background;
	sf::Sprite horizontal;
	sf::Sprite vertical;
	sf::Vector2f buttonSize;
	sf::Sprite carrier;
	boardCirles points[8][8];
	sf::Text boardText;
	sf::Text verticalText;
	sf::Text horizontalText;
	sf::Font timesNewRoman;
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
	void clicked(sf::Vector2i mouseClickedPos);
	void setShip(sf::Vector2i mouseClickedPos, sf::RenderWindow& window, int whichShip);
};





#endif