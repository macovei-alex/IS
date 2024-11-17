#pragma once

#include "IScene.h"
#include "IWindow.h"
#include "Pacman.h"
#include "Maze.h"
#include "GameplaySettings.h"

#include <unordered_map>


namespace pac
{
	class GameplayScene : public IScene
	{
	public:
		GameplayScene(std::shared_ptr<IWindow> window, Maze&& maze, const GameplaySettings& settings);
		void AddListener(std::shared_ptr<IListener> listener, EventType eventType) override;
		void RemoveListener(std::shared_ptr<IListener> listener, EventType eventType) override;
		void Notify(std::shared_ptr<IEvent> newEvent) override;

		void Draw() const override;
		void NextTick() override;

	private:
		void RemoveExpiredListeners();

	private:
		std::shared_ptr<IWindow> mWindow;
		Maze mMaze;
		Pacman mPacman;
		GameplaySettings mSettings;
		// TODO: Add ghosts and GameplaySettings
		std::unordered_map<EventType, std::vector<std::weak_ptr<IListener>>> mListeners;
	};
}
