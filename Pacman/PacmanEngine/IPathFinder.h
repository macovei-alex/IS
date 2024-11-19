#pragma once

#include "Position.h"
#include "Maze.h"
#include "Pacman.h"

namespace pac
{
    class IPathFinder
    {
    public:
        virtual ~IPathFinder() = default;
		virtual Position NextMove(const Maze& maze, const Pacman& pacman) const = 0;
   
    };
}
