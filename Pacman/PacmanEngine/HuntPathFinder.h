#pragma once

#include "IPathFinder.h"
#include "Ghost.h"


namespace pac
{
	class HuntPathFinder : public IPathFinder
	{
	public:
		HuntPathFinder(Ghost* ghost);
		Position NextMove(const Maze& maze, const Pacman& pacman) const override;

	private:
		Ghost* mGhost;
	};
}
