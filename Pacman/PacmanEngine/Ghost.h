#pragma once

#include "Position.h"
#include "IPathFinder.h"
#include "Maze.h"
#include "Pacman.h"
#include "Textures.h"

namespace pac
{
    class Ghost
    {
    public:
        Ghost(Position initialPosition, const IPathFinder& pathFinder);


        void Update(const Maze& maze, const Pacman& pacman);
        void Draw(IWindow* window) const;
        Position GetCurrentPosition() const;

    private:
        Position mCurrentPosition;
        const IPathFinder& mPathFinder;
    };
}
