#include "ScaredPathFinder.h"
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <limits>

namespace pac
{
    ScaredPathFinder::ScaredPathFinder(const Ghost* ghost)
    {
        AttachTo(ghost);
    }

    Position ScaredPathFinder::NextMove(const Maze& maze, const Pacman& pacman)
    {
        Position ghostPosition = mGhost->GetPosition();
        Position pacmanPosition = pacman.GetPosition();

        std::map<Position, int> distances; 
        std::queue<Position> bfsQueue;
        std::set<Position> visited;


        bfsQueue.push(pacmanPosition);
        distances[pacmanPosition] = 0;
        visited.insert(pacmanPosition);

        while (!bfsQueue.empty())
        {
            Position current = bfsQueue.front();
            bfsQueue.pop();

            for (const auto& direction : Direction::AllDirections())
            {
                Position neighbor = Add(current, direction);
                if (visited.find(neighbor) == visited.end() && maze.GetCellType(neighbor) != CellType::Wall)
                {
                    visited.insert(neighbor);
                    distances[neighbor] = distances[current] + 1;
                    bfsQueue.push(neighbor);
                }
            }
        }

        Position bestMove = ghostPosition;
        int maxDistance = -1;

        for (const auto& direction : Direction::AllDirections())
        {
            Position neighbor = Add(ghostPosition, direction);

            if (maze.GetCellType(neighbor) != CellType::Wall && distances.find(neighbor) != distances.end())
            {
                int distance = distances[neighbor];
                if (distance > maxDistance)
                {
                    maxDistance = distance;
                    bestMove = neighbor;
                }
            }
        }

        return bestMove;
    }

    void ScaredPathFinder::AttachTo(const Ghost* ghost)
    {
        mGhost = ghost;
    }
}
