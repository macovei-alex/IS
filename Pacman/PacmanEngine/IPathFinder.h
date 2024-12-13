#pragma once

#include "Position.h"
#include "Maze.h"
#include "Pacman.h"

namespace pac
{
	class Ghost;

	/**
  * @class IPathFinder
  * @brief Interface for pathfinding strategies.
  */
	class IPathFinder
	{
	public:
		/**
   * @brief Virtual destructor for IPathFinder.
   */
		virtual ~IPathFinder() = default;

		/**
   * @brief Determines the next move for the ghost.
   * @param maze Reference to the maze.
   * @param pacman Reference to Pacman.
   * @return The next position for the ghost.
   */
		virtual Position NextMove(const Maze& maze, const Pacman& pacman) = 0;

		/**
   * @brief Attaches the pathfinder to a ghost.
   * @param ghost Pointer to the ghost.
   */
		virtual void AttachTo(const Ghost* ghost) = 0;
	};
}
