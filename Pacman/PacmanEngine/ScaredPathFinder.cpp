#include "ScaredPathFinder.h"
#include <cmath>
#include <queue>
#include <map>
#include <set>
#include <limits>

namespace pac
{
    Position ScaredPathFinder::NextMove(const Maze& maze, const Pacman& pacman)
    {
        Position ghostPosition = maze.GetGhostSpawnPosition();
        Position pacmanPosition = pacman.GetPosition();
        std::vector<Direction> directions = {
            Direction::Up(), Direction::Down(), Direction::Left(), Direction::Right()
        };

        std::queue<Position> bfsQueue;
        std::map<Position, Position> parent;
        std::set<Position> visited;

        bfsQueue.push(ghostPosition);
        visited.insert(ghostPosition);

        Position farthestPosition = ghostPosition;
        double maxDistance = -1.0;

        // Folosim BFS pentru a explora harta si a gasi cel mai îndepărtat punct față de Pacman
        while (!bfsQueue.empty())
        {
            Position current = bfsQueue.front();
            bfsQueue.pop();

            double distance = std::sqrt(
                std::pow(current.row - pacmanPosition.row, 2) +
                std::pow(current.col - pacmanPosition.col, 2));

            // Dacă distanța față de Pacman este mai mare decât cea mai mare distanță găsită până acum
            if (distance > maxDistance)
            {
                maxDistance = distance;
                farthestPosition = current;
            }

            // Explorează vecinii
            for (const Direction& direction : directions)
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
}
