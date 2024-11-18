#pragma once

#include "IScene.h"
#include "IWindow.h"
#include "IGame.h"
#include "Maze.h"
#include "GameplaySettings.h"

#include <vector>


namespace pac
{
	class Game : public IGame
	{
	public:
		Game(std::shared_ptr<IWindow> window, Maze&& maze, const GameplaySettings& settings);
		void AddScene(std::shared_ptr<IScene> scene);
		void Run() override;
		std::shared_ptr<IScene> GetCurrentScene() const;
	private:
		std::shared_ptr<IWindow> mWindow;
		std::vector<std::shared_ptr<IScene>> mScenes;
		size_t mCurrentSceneIndex = 0;
	};
}
