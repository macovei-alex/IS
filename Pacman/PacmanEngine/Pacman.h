#pragma once

#include "IListener.h"
#include "Maze.h"
#include "GameplaySettings.h"
#include "Direction.h"

namespace pac
{
	/**
  * @class Pacman
  * @brief Represents Pacman in the game.
  */
	class Pacman : public IListener
	{
	public:
		/**
   * @brief Constructs a Pacman object.
   * @param initialPosition The initial position of Pacman.
   * @param ticksPerMove The number of ticks per move.
   * @param powerUpDuration The duration of the power-up effect.
   */
		Pacman(Position initialPosition, TickType ticksPerMove, TickType powerUpDuration);

		/**
   * @brief Tries to move Pacman in the maze.
   * @param maze Reference to the maze.
   * @return The type of the cell Pacman moved to.
   */
		CellType TryMove(Maze& maze);

		/**
   * @brief Gets the position of Pacman.
   * @return The position of Pacman.
   */
		Position GetPosition() const;

		/**
   * @brief Sets the power-up state for Pacman.
   */
		void SetPowerUp();

		/**
   * @brief Checks if Pacman is powered up.
   * @return True if Pacman is powered up, false otherwise.
   */
		bool IsPoweredUp() const;

		/**
   * @brief Draws Pacman.
   * @param window Pointer to the game window.
   */
		void Draw(IWindow* window) const;

		/**
   * @brief Handles events for Pacman.
   * @param event Pointer to the event.
   */
		void OnEvent(const IEvent* event) override;

	private:
		Position mPosition; ///< The current position of Pacman.
		Direction mDirection; ///< The current direction of Pacman.
		Direction mNextDirection; ///< The next direction Pacman will move.
		TickType mTick; ///< The current tick.
		TickType mTicksPerMove; ///< The number of ticks per move.
		TickType mLastPowerUpStart; ///< The tick when the last power-up started.

	private:
		const TickType mPowerUpDuration; ///< The duration of the power-up effect.
	};
}