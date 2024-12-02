#include "Logger/Logger.h"
#include "SFMLWindow.h"

#include "PacmanEngine/GameplayScene.h"
#include "PacmanEngine/Game.h"


int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(1500, 1000), "Pacman Game");
	pac::GameplaySettings settings;

	pac::Maze maze;
	maze.ReadMazeFromFile("assets\\maze.txt");

	std::unique_ptr<pac::IWindow> iWindow = std::make_unique<pac::SFMLWindow>
		(renderWindow, pac::AssetManager("assets"));

	pac::Game game(std::move(iWindow), std::move(maze), settings);
	game.Run();

	return 0;
}