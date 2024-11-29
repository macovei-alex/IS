#include "RoamingPathFinder.h"
#include <cstdlib> // for rand()
#include <ctime>
#include <vector>

namespace pac
{
	RoamingPathFinder::RoamingPathFinder(const Ghost* ghost)
		: mCurrentDirection(Direction::Up())
	{
		AttachTo(ghost);
	}

	Position RoamingPathFinder::NextMove(const Maze& maze, const Pacman& pacman)
	{
		Position currentPosition = mGhost->GetPosition();

		std::vector<Direction> directions = Direction::AllDirections();

		directions.erase(std::remove(directions.begin(), directions.end(), mCurrentDirection.Opposite()), directions.end());

		std::vector<Direction> validDirections;
		for (Direction dir : directions)
		{
			Position newPos = Add(currentPosition, dir);
			if (maze.IsWalkable(newPos))
			{
				validDirections.push_back(dir);
			}
		}

		if (!validDirections.empty())
		{
			mCurrentDirection = validDirections[std::rand() % validDirections.size()];
			return Add(currentPosition, mCurrentDirection);
		}

		return currentPosition;
	}

	void RoamingPathFinder::AttachTo(const Ghost* ghost)
	{
		mGhost = ghost;
	}
}
