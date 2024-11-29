#include "WaitingPathFinder.h"


namespace pac
{
	WaitingPathFinder::WaitingPathFinder(const Ghost* ghost, TickType delay)
		: mTargetTick(ghost->GetTick() + delay)
	{
		AttachTo(ghost);
	}

	Position WaitingPathFinder::NextMove(const Maze& maze, const Pacman& pacman)
	{
		if (mGhost->GetTick() < mTargetTick)
		{
			return mGhost->GetPosition();
		}

		return Position::GetInvalid();
	}

	void WaitingPathFinder::AttachTo(const Ghost* ghost)
	{
		mGhost = ghost;
	}
}
