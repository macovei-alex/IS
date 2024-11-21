#include "Ghost.h"

namespace pac
{
    Ghost::Ghost(Position initialPosition, const IPathFinder& pathFinder)
        : mCurrentPosition(initialPosition), mPathFinder(pathFinder) {
    }

    void Ghost::Update(const Maze& maze, const Pacman& pacman)
    {
        static Position lastPacmanPosition = pacman.GetCurrentPosition();

        // Wait for Pacman to move before updating
        if (pacman.GetCurrentPosition() != lastPacmanPosition)
        {
            mCurrentPosition = mPathFinder.NextMove(maze, pacman);
            lastPacmanPosition = pacman.GetCurrentPosition();
        }
    }
 

    void Ghost::Draw(IWindow* window) const
    {
        window->DrawTexture(mCurrentPosition, Textures::Ghost);
    }

    Position Ghost::GetCurrentPosition() const
    {
        return mCurrentPosition;
    }
}

