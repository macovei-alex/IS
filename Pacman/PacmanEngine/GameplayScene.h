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
		SceneState NextTick() override;

		void AddListener(std::weak_ptr<IListener> listener, EventType eventType) override;
		void RemoveListener(const IListener* listener, EventType eventType) override;
		void Notify(IEvent* event) const override;

	private:
		SceneState HandleEvents();
		SceneState HandleCollision(Ghost& ghost);
		void HandleStateTransition(Ghost& ghost);

	private:
		CollisionType PacmanCollisionWith(const Ghost& ghost) const;
		bool SeesPacman(const Ghost& ghost) const;
		bool IsGameWon() const;
		void RemoveExpiredListeners();

	private:
		IWindow* mWindow;
		Maze mMaze;
		std::shared_ptr<Pacman> mPacman;
		const GameplaySettings& mSettings;
		std::vector<Ghost> mGhosts;
		std::unordered_map<EventType, std::vector<std::weak_ptr<IListener>>> mListeners;
		ScoreType mScore;
		uint16_t mCollectibleEntities;
	};
}
