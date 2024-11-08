#include "pch.h"
#include "Logger.h"

int main()
{
	Logger::cout.Info("Hello, World!");

	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color::Black);

		// window.draw(...);

		window.display();
	}
}
