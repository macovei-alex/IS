#pragma once

#include "IPathFinder.h"

namespace pac
{
	class ScaredPathFinder : public IPathFinder
	{
	public:
		Position NextMove(const Maze& maze, const Pacman& pacman) const override;
	};
}
