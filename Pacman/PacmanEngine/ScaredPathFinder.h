#pragma once

#include "IPathFinder.h"
#include "Ghost.h"

namespace pac
{
	class ScaredPathFinder : public IPathFinder
	{
	public:
		ScaredPathFinder(Ghost* ghost);
		Position NextMove(const Maze& maze, const Pacman& pacman) override;

	private:
		Ghost* mGhost;
	};
}
