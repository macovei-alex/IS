#pragma once

#include "IPathFinder.h"
#include "Ghost.h"
#include <stack>

namespace pac
{
	/**
  * @class HuntPathFinder
  * @brief Pathfinding strategy for hunting Pacman.
  */
	class HuntPathFinder : public IPathFinder
	{
	public:
		/**
   * @brief Constructs a HuntPathFinder.
   * @param ghost Pointer to the ghost using this pathfinder.
   */
		HuntPathFinder(const Ghost* ghost);

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
		Position mLastPacmanPosition; ///< Last known position of Pacman.
		std::vector<Position> mPath; ///< Path to follow.
	};
}
