#ifndef BOARD
#define BOARD

#include <SFML\Graphics.hpp>
#include <math.h>

class Board {
private:
	sf::Texture backgroundTexture;
	sf::Sprite background;
	sf::CircleShape points[8][8];
	const int numOfCols;
	const int numOfRows;
	const int xPixals;
	const int yPixals;
	const int pointRadius;
	const int seperationOfPoints;
	const int xOffset;
	const int yOffset;

public:
	Board();
	void draw(sf::RenderWindow& window);
	void hover(sf::Vector2i cursorPos);

};





#endif