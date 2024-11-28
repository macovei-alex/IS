#include "RoamingPathFinder.h"
#include <cstdlib> // pentru rand()
#include <ctime>
#include <vector>

namespace pac
{
    RoamingPathFinder::RoamingPathFinder(Ghost* ghost)
        : mGhost(ghost)
    {
        std::srand(static_cast<unsigned>(std::time(nullptr))); 
        mCurrentDirection = Direction::Up(); 
    }

    Position RoamingPathFinder::NextMove(const Maze& maze, const Pacman& pacman)
    {
        Position currentPosition = mGhost->GetPosition();

        std::vector<Direction> directions = { Direction::Up(), Direction::Down(), Direction::Left(), Direction::Right() };

        directions.erase(std::remove(directions.begin(), directions.end(), OppositeDirection(mCurrentDirection)), directions.end());

        std::vector<Direction> validDirections;
        for (const auto& dir : directions)
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

    Direction RoamingPathFinder::OppositeDirection(const Direction& direction) const
    {
        if (direction == Direction::Up()) return Direction::Down();
        if (direction == Direction::Down()) return Direction::Up();
        if (direction == Direction::Left()) return Direction::Right();
        if (direction == Direction::Right()) return Direction::Left();
        return Direction::Up(); 
    }
}
