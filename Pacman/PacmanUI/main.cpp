#include "pch.h"
#include "Logger/Logger.h"
#include "PacmanEngine/Game.h"

int main()
{
	pac::Game game;
	game.TestFunc();

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