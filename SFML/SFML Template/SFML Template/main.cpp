#include <SFML\Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(1000,1000), "First Try");
	sf::Vector2f shape(110, 110);
	sf::RectangleShape rect(shape);


	while (window.isOpen()) {
		//Handle events

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		//update
		window.clear();

		//Draw objects

		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 50; j++) {
				rect.setPosition((110 * i) + 15* i, (110 * j) + 15 * j);
				window.draw(rect);
			}
		}

		window.display();
	}

	return 0;
}