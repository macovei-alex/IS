#pragma once

#include "IPathFinder.h"

namespace pac
{
    class HuntPathFinder : public IPathFinder
    {
    public:
        Position NextMove(const Maze& maze, const Pacman& pacman) const override {};
       
    };
}
