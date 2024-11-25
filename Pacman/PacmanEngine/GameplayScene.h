#pragma once

#include "IScene.h"
#include "IWindow.h"
#include "Pacman.h"
#include "Maze.h"
#include "GameplaySettings.h"

#include <unordered_map>
#include "Ghost.h"
#include "HuntPathFinder.h"
#include "ScaredPathFinder.h"


namespace pac
{
	enum class CollisionType : uint8_t
	{
		NoCollision,
		NoPowerUp,
		PoweredUp
	};

	class GameplayScene : public IScene
	{
	public:
		GameplayScene(IWindow* window, Maze&& maze, const GameplaySettings& settings);

		void AddListener(std::weak_ptr<IListener> listener, EventType eventType) override;
		void RemoveListener(std::weak_ptr<IListener> listener, EventType eventType) override;
		void Notify(IEvent* newEvent) const override;

		void Draw() const override;
		void NextTick() override;

		CollisionType PacmanCollidesWith(Ghost& ghost) const;

	private:
		void RemoveExpiredListeners();

	private:
		IWindow* mWindow;
		Maze mMaze;
		std::shared_ptr<Pacman> mPacman;
		const GameplaySettings& mSettings;
		std::vector<pac::Ghost> mGhosts; 
		std::unordered_map<EventType, std::vector<std::weak_ptr<IListener>>> mListeners;
		uint64_t mScore = 0;
	};
}
