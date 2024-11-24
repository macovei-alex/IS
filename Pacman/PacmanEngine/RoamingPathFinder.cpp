#include "RoamingPathFinder.h"
#include <cstdlib> // pentru rand()
#include <ctime>   

pac::RoamingPathFinder::RoamingPathFinder(Ghost* ghost)
	: mGhost(ghost)
{
	// empty
}

pac::Position pac::RoamingPathFinder::NextMove(const Maze& maze, const Pacman& pacman) const
{

    std::vector<Direction> directions = { Direction::Up(), Direction::Down(), Direction::Left(), Direction::Right() };
    int randomIndex = rand() % directions.size(); 

    Position newPos = Add(mGhost->GetCurrentPosition(), directions[randomIndex]);

    if (maze.IsWalkable(newPos))
    {
        return newPos;  
    }

    for (const auto& dir : directions)
    {
        Position fallbackPos = Add(mGhost->GetCurrentPosition(), dir);
        if (maze.IsWalkable(fallbackPos))
        {
            return fallbackPos;
        }
    }
    return mGhost->GetCurrentPosition();
}
