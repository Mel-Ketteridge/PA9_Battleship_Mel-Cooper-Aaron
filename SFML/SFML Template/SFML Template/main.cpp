#include <SFML\Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(640,480), "SFML Tutorial");
	window.display();

	/*while (window.isOpen()) {
		//Handle events

		//update
		window.clear();

		//Draw objects

		window.display();
	}*/

	return 0;
}