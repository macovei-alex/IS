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

		void Draw() const override;
		void NextTick() override;

		CollisionType PacmanCollidesWith(const Ghost& ghost) const;
		bool IsGameOver();
		bool IsWinGame();

		void AddListener(std::weak_ptr<IListener> listener, EventType eventType) override;
		void RemoveListener(std::weak_ptr<IListener> listener, EventType eventType) override;
		void Notify(IEvent* event) const override;

	private:
		void RemoveExpiredListeners();

	private:
		IWindow* mWindow;
		Maze mMaze;
		std::shared_ptr<Pacman> mPacman;
		const GameplaySettings& mSettings;
		std::vector<Ghost> mGhosts;
		std::unordered_map<EventType, std::vector<std::weak_ptr<IListener>>> mListeners;
		ScoreType mScore;
		ScoreType mMaximumScore;
	};
}
