#include "DelayedRoamingPathFinder.h"


namespace pac
{
	DelayedRoamingPathFinder::DelayedRoamingPathFinder(Ghost* ghost, TickType delay)
		: RoamingPathFinder(ghost)
		, mTick(0)
		, mDelay(delay)
	{
		// empty
	}

	Position DelayedRoamingPathFinder::NextMove(const Maze& maze, const Pacman& pacman)
	{
		if (mTick < mDelay)
		{
			++mTick;
			return mGhost->GetPosition();
		}

		return RoamingPathFinder::NextMove(maze, pacman);
	}
}
