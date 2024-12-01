#include "HuntPathFinder.h"

#include "Logger/Logger.h"

#include <queue>
#include <vector>
#include <array>


pac::HuntPathFinder::HuntPathFinder(const Ghost* ghost)
	: mLastPacmanPosition(Position::GetInvalid())
	, mPath()
{
	AttachTo(ghost);
}

pac::Position pac::HuntPathFinder::NextMove(const Maze& maze, const Pacman& pacman)
{
	if (bool seeEachOther = maze.SeeEachOther(pacman.GetPosition(), mGhost->GetPosition());
		seeEachOther || mPath.size() == 0)
	{
		mPath = maze.CalculateShortestPath(mGhost->GetPosition(), pacman.GetPosition());
	}

	Position temp = mPath.back();
	mPath.pop_back();
	return temp;
}

void pac::HuntPathFinder::AttachTo(const Ghost* ghost)
{
	mGhost = ghost;
}
