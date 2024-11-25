#include "ScaredPathFinder.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>

namespace pac
{
	Position ScaredPathFinder::NextMove(const Maze& maze, const Pacman& pacman)
	{
		/*
		Position ghostPosition = maze.GetGhostSpawnPosition();
		Position pacmanPosition = pacman.GetPosition();
		std::vector<Direction> directions = {
			Direction::Down(), Direction::Up(), Direction::Right(), Direction::Left()
		};

		std::queue<Position> bfsQueue;
		std::map<Position, Position> parent;
		std::set<Position> visited;

		bfsQueue.push(ghostPosition);
		visited.insert(ghostPosition);

		Position farthestPoint = ghostPosition;
		double maxDistance = -1.0;

		while (!bfsQueue.empty())
		{
			Position current = bfsQueue.front();
			bfsQueue.pop();

			// Calculate distance from Pacman
			double distance = std::sqrt(std::pow(current.row - pacmanPosition.row, 2) +
				std::pow(current.col - pacmanPosition.col, 2));

			if (distance > maxDistance)
			{
				maxDistance = distance;
				farthestPoint = current;
			}


			for (const Direction& direction : directions)
			{
				Position neighbor = Add(current, direction);

				if (visited.find(neighbor) == visited.end() &&
					maze.GetCellType(neighbor) != CellType::Wall)
				{
					bfsQueue.push(neighbor);
					visited.insert(neighbor);
					parent[neighbor] = current;
				}
			}
		}

		Position nextMove = farthestPoint;
		while (parent.find(nextMove) != parent.end() && parent[nextMove] != ghostPosition)
		{
			nextMove = parent[nextMove];
		}
		*/

		return pacman.GetPosition();
	}
}
