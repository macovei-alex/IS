#pragma once

#include "IPathFinder.h"
#include "Ghost.h"



namespace pac
{
	class RoamingPathFinder : public IPathFinder
	{
	public:
		RoamingPathFinder(Ghost* ghost);
		Position NextMove(const Maze& maze, const Pacman& pacman) override;

		Direction OppositeDirection(const Direction& direction) const;

	protected:
		Ghost* mGhost;
		Direction mCurrentDirection;
	};
}