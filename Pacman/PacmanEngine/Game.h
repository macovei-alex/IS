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
	class Game : public IGame, public IListener
	{
	public:
		Game(std::shared_ptr<IWindow> window, Maze&& maze, const GameplaySettings& settings);
		void AddScene(std::shared_ptr<IScene> scene);
		void Run() override;
		std::shared_ptr<IScene> GetCurrentScene() const;

		void OnEvent(std::shared_ptr<IEvent> event) override;

	private:
		std::shared_ptr<IWindow> mWindow;
		std::vector<std::shared_ptr<IScene>> mScenes;
		size_t mCurrentSceneIndex = 0;
	};
}
