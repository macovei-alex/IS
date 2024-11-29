#include "ScaredPathFinder.h"
#include <cmath>
#include <queue>
#include <map>
#include <set>
#include <limits>

namespace pac
{
	ScaredPathFinder::ScaredPathFinder(const Ghost* ghost)
		: mGhost(ghost)
	{
		// empty
	}

	Position ScaredPathFinder::NextMove(const Maze& maze, const Pacman& pacman)
	{
		Position ghostPosition = mGhost->GetPosition();
		Position pacmanPosition = pacman.GetPosition();

		std::queue<Position> bfsQueue;
		std::map<Position, Position> parent;
		std::set<Position> visited;

		bfsQueue.push(ghostPosition);
		visited.insert(ghostPosition);

		Position farthestPosition = ghostPosition;
		decltype(Position::row) maxDistance = 0;

		// Folosim BFS pentru a explora harta si a gasi cel mai îndepărtat punct față de Pacman
		while (!bfsQueue.empty())
		{
			Position current = bfsQueue.front();
			bfsQueue.pop();

			auto distance = current.NumberOfCellsTo(pacmanPosition);

			// Dacă distanța față de Pacman este mai mare decât cea mai mare distanță găsită până acum
			if (distance > maxDistance)
			{
				maxDistance = distance;
				farthestPosition = current;
			}

			// Explorează vecinii
			for (Direction direction : Direction::AllDirections())
			{
				Position neighbor = Add(current, direction);

				// Verificăm dacă nu este un zid și dacă nu am vizitat deja această poziție
				if (visited.find(neighbor) == visited.end() && maze.GetCellType(neighbor) != CellType::Wall)
				{
					// Verificăm dacă poziția vecină nu este Pacman
					if (neighbor != pacmanPosition)
					{
						bfsQueue.push(neighbor);
						visited.insert(neighbor);
						parent[neighbor] = current;
					}
				}
			}
		}

		// Alege calea care maximizează distanța față de Pacman
		Position nextMove = farthestPosition;
		while (parent.find(nextMove) != parent.end() && parent[nextMove] != ghostPosition)
		{
			nextMove = parent[nextMove];
		}

		return nextMove;
	}

	void ScaredPathFinder::Attach(Ghost* ghost)
	{
		mGhost = ghost;
	}
}
