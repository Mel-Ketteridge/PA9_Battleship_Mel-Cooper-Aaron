#ifndef BOARDCIRCLES
#define BOARDCIRCLES

#include <SFML\Graphics.hpp>

//Allows us to add variables to the circles on the board (such as hit or miss)
class boardCirles: public sf::CircleShape{
	bool clicked;
	bool isOccupied;
	int ship;

public:
	boardCirles() {
		clicked = false;
		isOccupied = false;
		ship = -1;
	}

	bool getClicked() {
		return clicked;
	}

	void setClicked(bool set) {
		clicked = set;
	}

	bool getIsOccupied() {
		return isOccupied;
	}

	void setIsOccupied(bool set) {
		isOccupied = set;
	}

	int getShip() {
		return ship;
	}

	void setShip(int set) {
		ship = set;
	}
};



#endif