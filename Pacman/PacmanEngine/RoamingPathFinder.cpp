#include "RoamingPathFinder.h"


pac::RoamingPathFinder::RoamingPathFinder(const Ghost* ghost)
{
	AttachTo(ghost);
}

pac::Position pac::RoamingPathFinder::NextMove(const Maze& maze, const Pacman& pacman)
{
	if (mPath.empty())
	{
		Position target;
		do
		{
			target = maze.GetRandomWalkablePosition();
		} while (target == mGhost->GetPosition());

		mPath = maze.CalculateShortestPath(mGhost->GetPosition(), target);
		if (mPath.empty())
		{
			mPath.push_back(mGhost->GetPosition());
		}
	}

	Position temp = mPath.back();
	mPath.pop_back();
	return temp;
}

void pac::RoamingPathFinder::AttachTo(const Ghost* ghost)
{
	mGhost = ghost;
}
