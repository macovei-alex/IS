#pragma once

#include "Position.h"
#include "IPathFinder.h"
#include "Maze.h"
#include "Pacman.h"
#include "Textures.h"
#include "GameplaySettings.h"

namespace pac
{
	/**
  * @class Ghost
  * @brief Represents a ghost in the game.
  */
	class Ghost
	{
	public:
		/**
   * @enum State
   * @brief Represents the state of the ghost.
   */
		enum class State : uint8_t
		{
			Hunting,
			Scared,
			Roaming,
			Dead
		};

	public:
		/**
   * @brief Constructs a Ghost object.
   * @param spawnPos The spawn position of the ghost.
   * @param firstSpawnDelay The initial spawn delay.
   * @param settings The gameplay settings.
   */
		Ghost(Position spawnPos, TickType firstSpawnDelay, const GameplaySettings& settings);

		// Delete copy constructor and copy assignment operator
		Ghost(const Ghost& other) = delete;
		void operator=(const Ghost& other) = delete;

		// Move constructor
		Ghost(Ghost&& other) noexcept;

		// Delete move assignment operator
		void operator=(Ghost&& other) = delete;

		/**
   * @brief Advances the ghost to the next tick.
   * @param maze Reference to the maze.
   * @param pacman Reference to Pacman.
   */
		void NextTick(const Maze& maze, const Pacman& pacman);

		/**
   * @brief Draws the ghost.
   * @param window Pointer to the game window.
   */
		void Draw(IWindow* window) const;

		/**
   * @brief Gets the position of the ghost.
   * @return The position of the ghost.
   */
		Position GetPosition() const;

		/**
   * @brief Sets the state of the ghost.
   * @param state The new state of the ghost.
   */
		void SetState(State state);

		/**
   * @brief Gets the state of the ghost.
   * @return The state of the ghost.
   */
		State GetState() const;

		/**
   * @brief Gets the current tick of the ghost.
   * @return The current tick of the ghost.
   */
		TickType GetTick() const;

	private:
		Position mPosition; ///< The current position of the ghost.
		TickType mTick; ///< The current tick of the ghost.
		TickType mTicksPerMove; ///< Ticks per move when not scared.
		TickType mTicksPerMoveScared; ///< Ticks per move when scared.
		TickType mRespawnDelay; ///< Respawn delay.
		std::unique_ptr<IPathFinder> mPathFinder; ///< Unique pointer to the pathfinder.
		State mState; ///< The current state of the ghost.

	private:
		const Position mSpawnPosition; ///< The spawn position of the ghost.
	};

	/**
  * @brief Converts a ghost state to a string.
  * @param state The state of the ghost.
  * @return The string representation of the state.
  */
	std::string_view StateToStr(Ghost::State state);
}
