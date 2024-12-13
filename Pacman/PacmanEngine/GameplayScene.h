#pragma once

#include "IScene.h"
#include "IWindow.h"
#include "Pacman.h"
#include "Maze.h"
#include "GameplaySettings.h"
#include "Ghost.h"
#include <unordered_map>

namespace pac
{
	/**
  * @enum CollisionType
  * @brief Represents the type of collision.
  */
	enum class CollisionType : uint8_t
	{
		NoCollision,
		NoPowerUp,
		PoweredUp
	};

	/**
  * @class GameplayScene
  * @brief Manages the gameplay scene.
  */
	class GameplayScene : public IScene
	{
	public:
		/**
   * @brief Constructs a GameplayScene.
   * @param window Pointer to the game window.
   * @param maze The maze for the game.
   * @param settings The gameplay settings.
   */
		GameplayScene(IWindow* window, Maze&& maze, const GameplaySettings& settings);

		/**
   * @brief Draws the scene.
   */
		void Draw() const override;

		/**
   * @brief Advances the scene to the next tick.
   * @return The state of the scene after the tick.
   */
		SceneState NextTick() override;

		/**
   * @brief Adds a listener for a specific event type.
   * @param listener Weak pointer to the listener.
   * @param eventType The type of event to listen for.
   */
		void AddListener(std::weak_ptr<IListener> listener, EventType eventType) override;

		/**
   * @brief Removes a listener for a specific event type.
   * @param listener Pointer to the listener.
   * @param eventType The type of event to stop listening for.
   */
		void RemoveListener(const IListener* listener, EventType eventType) override;

		/**
   * @brief Notifies listeners of an event.
   * @param event Pointer to the event.
   */
		void Notify(IEvent* event) const override;

	private:
		/**
   * @brief Handles events in the scene.
   * @return The state of the scene after handling events.
   */
		SceneState HandleEvents();

		/**
   * @brief Handles collision with a ghost.
   * @param ghost Reference to the ghost.
   * @return The state of the scene after handling the collision.
   */
		SceneState HandleCollision(Ghost& ghost);

		/**
   * @brief Handles state transition for a ghost.
   * @param ghost Reference to the ghost.
   */
		void HandleStateTransition(Ghost& ghost);

		/**
   * @brief Checks for collision between Pacman and a ghost.
   * @param ghost Reference to the ghost.
   * @return The type of collision.
   */
		CollisionType PacmanCollisionWith(const Ghost& ghost) const;

		/**
   * @brief Checks if a ghost sees Pacman.
   * @param ghost Reference to the ghost.
   * @return True if the ghost sees Pacman, false otherwise.
   */
		bool SeesPacman(const Ghost& ghost) const;

		/**
   * @brief Checks if the game is won.
   * @return True if the game is won, false otherwise.
   */
		bool IsGameWon() const;

		/**
   * @brief Removes expired listeners.
   */
		void RemoveExpiredListeners();

	private:
		IWindow* mWindow; ///< Pointer to the game window.
		Maze mMaze; ///< The maze for the game.
		std::shared_ptr<Pacman> mPacman; ///< Shared pointer to Pacman.
		const GameplaySettings& mSettings; ///< Gameplay settings.
		std::vector<Ghost> mGhosts; ///< Vector of ghosts.
		std::unordered_map<EventType, std::vector<std::weak_ptr<IListener>>> mListeners; ///< Map of event listeners.
		ScoreType mScore; ///< The current score.
		uint16_t mCollectibleEntities; ///< Number of collectible entities.
	};
}
