#include "WaitingPathFinder.h"


namespace pac
{
	WaitingPathFinder::WaitingPathFinder(const Ghost* ghost, TickType delay)
		: mGhost(ghost)
		, mTick(0)
		, mDelay(delay)
	{
		// empty
	}

	Position WaitingPathFinder::NextMove(const Maze& maze, const Pacman& pacman)
	{
		if (mTick < mDelay)
		{
			++mTick;
			return mGhost->GetPosition();
		}

		return Position::GetInvalid();
	}

	void WaitingPathFinder::Attach(Ghost* ghost)
	{
		mGhost = ghost;
	}
}
