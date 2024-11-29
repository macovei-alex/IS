#pragma once

#include "Position.h"
#include "Maze.h"
#include "Pacman.h"

namespace pac
{
	class Ghost;

	class IPathFinder
	{
	public:
		virtual ~IPathFinder() = default;
		virtual Position NextMove(const Maze& maze, const Pacman& pacman) = 0;
		virtual void AttachTo(const Ghost* ghost) = 0;
	};
}
