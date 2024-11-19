#include "Logger/Logger.h"
#include "AssetManager.h"
#include "SFMLWindow.h"
#include "PacmanEngine/IScene.h"
#include "PacmanEngine/IGame.h"
#include "PacmanEngine/GameplayScene.h"
#include "PacmanEngine/Game.h"


int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(1500, 1000), "Pacman Game");

	pac::Maze maze;
	maze.ReadMazeFromFile("assets\\maze.txt");

	std::unique_ptr<pac::IWindow> iWindow = std::make_unique<pac::SFMLWindow>
		(renderWindow, pac::AssetManager("assets"));

	pac::GameplaySettings settings;
	pac::Game game(std::move(iWindow), std::move(maze), settings);
	game.Run();

	return 0;
}