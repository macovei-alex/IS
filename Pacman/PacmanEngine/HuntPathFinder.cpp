#include "HuntPathFinder.h"

#include <queue>
#include <vector>
#include <array>


#define POS(pos) (pos.row * colCount + pos.col)


namespace pac
{
	HuntPathFinder::HuntPathFinder(Ghost* ghost)
		: mGhost(ghost)
	{
		// empty
	}

	Position HuntPathFinder::NextMove(const Maze& maze, const Pacman& pacman) const
	{
		const Dimensions dim = maze.GetDimensions();

		static std::vector<bool> visited(dim.rows * dim.cols, false);
		static std::vector<Position> parent(dim.rows * dim.cols, Position::GetInvalid());

		if (dim.rows * dim.cols > visited.size())
		{
			visited.resize(dim.rows * dim.cols);
			parent.resize(dim.rows * dim.cols);
		}

		for (size_t i = 0; i < visited.size(); i++)
		{
			visited[i] = false;
			parent[i] = Position::GetInvalid();
		}

		const auto colCount = maze.GetDimensions().cols;

		Position ghostPosition = mGhost->GetCurrentPosition();
		Position pacmanPosition = pacman.GetCurrentPosition();

		static constexpr std::array<Direction, 4> directions = {
			Direction::Down(), Direction::Up(), Direction::Right(), Direction::Left()
		};


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
				while (nextMove != ghostPosition && nextMove.IsValid())
				{
					current = nextMove;
					nextMove = parent[POS(nextMove)];
				}
				return current;
			}


			for (Direction direction : directions)
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

		return ghostPosition; 
	}
}