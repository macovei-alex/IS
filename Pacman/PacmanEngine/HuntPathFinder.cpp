#include "HuntPathFinder.h"
#include <queue>
#include <vector>
#include <map>
#include <set>

namespace pac {

    Position HuntPathFinder::NextMove(const Maze& maze, const Pacman& pacman) const
    {
        Position ghostPosition = maze.GetGhostSpawnPosition();
        Position pacmanPosition = pacman.GetCurrentPosition();

        std::vector<Direction> directions = {
            Direction::Down(), Direction::Up(), Direction::Right(), Direction::Left()
        };


        std::queue<Position> bfsQueue;
        std::map<Position, Position> parent; 
        std::set<Position> visited;

        bfsQueue.push(ghostPosition);
        visited.insert(ghostPosition);

        while (!bfsQueue.empty())
        {
            Position current = bfsQueue.front();
            bfsQueue.pop();


            if (current == pacmanPosition)
            {
                Position nextMove = current;


                while (parent[nextMove] != ghostPosition)
                {
                    nextMove = parent[nextMove];
                }
                return nextMove; 
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

        return ghostPosition; 
    }
}