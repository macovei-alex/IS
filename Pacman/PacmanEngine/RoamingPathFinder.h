#pragma once

#include "IPathFinder.h"
#include "Ghost.h"

namespace pac
{
	/**
  * @class RoamingPathFinder
  * @brief Pathfinding strategy for roaming behavior.
  */
	class RoamingPathFinder : public IPathFinder
	{
	public:
		/**
   * @brief Constructs a RoamingPathFinder.
   * @param ghost Pointer to the ghost using this pathfinder.
   */
		RoamingPathFinder(const Ghost* ghost);

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
		std::vector<Position> mPath; ///< Path to follow.
	};
}