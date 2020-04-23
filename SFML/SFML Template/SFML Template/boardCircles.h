#ifndef BOARDCIRCLES
#define BOARDCIRCLES

#include <SFML\Graphics.hpp>

//Allows us to add variables to the circles on the board (such as hit or miss)
class boardCirles: public sf::CircleShape{
	bool clicked;

public:
	boardCirles() {
		clicked = false;
	}

	bool getClicked() {
		return clicked;
	}

	void setClicked(bool set) {
		clicked = set;
	}
};


#endif