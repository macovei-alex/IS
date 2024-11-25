#pragma once

#include "IScene.h"
#include "IWindow.h"
#include "IGame.h"
#include "IListener.h"
#include "Maze.h"
#include "GameplaySettings.h"

#include <vector>


namespace pac
{
	class Game : public IGame
	{
	public:
		Game(std::unique_ptr<IWindow> window, Maze&& maze, const GameplaySettings& settings);
		void AddScene(std::unique_ptr<IScene> scene);
		void Run() override;
		IScene* GetCurrentScene() const;
		void LoseGame();

	private:
		std::unique_ptr<IWindow> mWindow;
		std::vector<std::unique_ptr<IScene>> mScenes;
		size_t mCurrentSceneIndex = 0;
		const GameplaySettings& mSettings;
	};
}
