#pragma once

#include "IPathFinder.h"
#include "Ghost.h"

namespace pac
{
	/**
  * @class WaitingPathFinder
  * @brief Pathfinding strategy for waiting behavior.
  */
	class WaitingPathFinder : public IPathFinder
	{
	public:
		/**
   * @brief Constructs a WaitingPathFinder.
   * @param ghost Pointer to the ghost using this pathfinder.
   * @param delay The delay before the ghost starts moving.
   */
		WaitingPathFinder(const Ghost* ghost, TickType delay);

		/**
   * @brief Determines the next move for the ghost.
   * @param maze Reference to the maze.
   * @param pacman Reference to Pacman.
   * @return The next position for the ghost.
   */
		Position NextMove(const Maze& maze, const Pacman& pacman) override;

		/**
   * @brief Attaches the pathfinder to a ghost.
   * @param ghost Pointer to the ghost.
   */
		void AttachTo(const Ghost* ghost) override;

	private:
		const Ghost* mGhost; ///< Pointer to the ghost using this pathfinder.
		TickType mTargetTick; ///< The target tick to start moving.
	};
}
