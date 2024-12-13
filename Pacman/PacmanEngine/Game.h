#pragma once

#include "IScene.h"
#include "IWindow.h"
#include "Maze.h"
#include "GameplaySettings.h"
#include <vector>

namespace pac
{
	/**
  * @class Game
  * @brief Manages the game lifecycle and scenes.
  */
	class Game
	{
	public:
		/**
   * @brief Constructs a Game object.
   * @param window Unique pointer to the game window.
   * @param maze The maze for the game.
   * @param settings The gameplay settings.
   * @param randomSeed The seed for random number generation (default is 0).
   */
		Game(std::unique_ptr<IWindow> window, Maze&& maze, const GameplaySettings& settings, uint32_t randomSeed = 0);

		/**
   * @brief Adds a scene to the game.
   * @param scene Unique pointer to the scene to add.
   */
		void AddScene(std::unique_ptr<IScene> scene);

		/**
   * @brief Runs the game loop.
   */
		void Run();

		/**
   * @brief Gets the current scene.
   * @return Pointer to the current scene.
   */
		IScene* GetCurrentScene() const;

	private:
		std::unique_ptr<IWindow> mWindow; ///< Unique pointer to the game window.
		std::vector<std::unique_ptr<IScene>> mScenes; ///< Vector of unique pointers to scenes.
		size_t mCurrentSceneIndex = 0; ///< Index of the current scene.
		GameplaySettings mSettings; ///< Gameplay settings.
	};
}
