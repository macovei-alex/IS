#include "pch.h"
#include "Logger/Logger.h"
#include "AssetManager.h"
#include "SFMLWindow.h"

int main() {

	//TODO: This should be from the backend through the IWindow interface and then using Game

    std::vector<std::vector<pac::CellType>> cells;
	cells.push_back({ pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall });
	cells.push_back({ pac::CellType::Wall, pac::CellType::Coin, pac::CellType::Coin, pac::CellType::GhostSpawn, pac::CellType::Wall });
	cells.push_back({ pac::CellType::Wall, pac::CellType::Coin, pac::CellType::PacmanSpawn, pac::CellType::Coin, pac::CellType::Wall });
	cells.push_back({ pac::CellType::Wall, pac::CellType::PowerUp, pac::CellType::Coin, pac::CellType::Coin, pac::CellType::Wall });
	cells.push_back({ pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall });

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pacman Game");

    pac::Maze maze;
    maze.InitCells(std::move(cells));

    //TODO: this should be relative path
	pac::AssetManager assetManager = pac::AssetManager("D:\\School\\3rd year\\1st sem\\IS\\IS\\Pacman\\PacmanUI");

    pac::SFMLWindow gameWindow(window, maze, assetManager);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        gameWindow.Draw();
        window.display();
    }

    return 0;
}