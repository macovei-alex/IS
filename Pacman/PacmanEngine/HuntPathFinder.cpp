#include "HuntPathFinder.h"

#include "Logger/Logger.h"

#include <queue>
#include <vector>
#include <array>


#define POS(pos) (pos.row * colCount + pos.col)


namespace pac
{
	HuntPathFinder::HuntPathFinder(const Ghost* ghost)
		: mLastPacmanPosition(Position::GetInvalid())
		, mPath()
	{
		AttachTo(ghost);
	}

	Position HuntPathFinder::NextMove(const Maze& maze, const Pacman& pacman)
	{
		if (bool seeEachOther = maze.SeeEachOther(pacman.GetPosition(), mGhost->GetPosition()); 
			seeEachOther || mPath.size() == 0)
		{
			if (seeEachOther)
			{
				Logger::cout.Debug("Pacman spotted. Recalculating path...");
			}
			UpdatePath(maze, pacman);
		}

		if (mPath.size() == 0)
		{
			return mGhost->GetPosition();
		}

		Position temp = mPath.top();
		mPath.pop();
		return temp;
	}

	void HuntPathFinder::UpdatePath(const Maze& maze, const Pacman& pacman)
	{
		const Dimensions dimensions = maze.GetDimensions();
		const uint64_t size = (uint64_t)dimensions.rows * dimensions.cols;

		static std::vector<bool> visited(size);
		static std::vector<Position> parent(size);

		if (size > visited.size())
		{
			visited.resize(size);
			parent.resize(size);
		}

		while (!mPath.empty())
		{
			mPath.pop();
		}

		for (size_t i = 0; i < visited.size(); i++)
		{
			visited[i] = false;
			parent[i] = Position::GetInvalid();
		}

		const auto colCount = dimensions.cols;

		const Position ghostPosition = mGhost->GetPosition();
		const Position pacmanPosition = pacman.GetPosition();

		std::queue<Position> bfsQueue;

		bfsQueue.push(ghostPosition);
		visited[POS(ghostPosition)] = true;

		while (!bfsQueue.empty())
		{
			Position current = bfsQueue.front();
			bfsQueue.pop();

			if (current == pacmanPosition)
			{
				Position nextMove = parent[POS(current)];
				mPath.push(current);
				while (nextMove != ghostPosition && nextMove.IsValid())
				{
					current = nextMove;
					nextMove = parent[POS(nextMove)];
					mPath.push(current);
				}
				break;
			}

			for (Direction direction : Direction::AllDirections())
			{
				Position neighbor = Add(current, direction);

				if (!visited[POS(neighbor)]
					&& maze.GetCellType(neighbor) != CellType::Wall)
				{
					bfsQueue.push(neighbor);
					visited[POS(neighbor)] = true;
					parent[POS(neighbor)] = current;
				}
			}
		}
	}

	void HuntPathFinder::AttachTo(const Ghost* ghost)
	{
		mGhost = ghost;
	}
}