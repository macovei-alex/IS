#pragma once

#include "Position.h"
#include "Maze.h"

namespace pac
{
    class IPathFinder
    {
    public:
        virtual ~IPathFinder() = default;

        virtual void SetDestination(const Position& destination) = 0;
        virtual Position NextMove(const Position& currentPosition, const Maze& maze) = 0;
        virtual bool IsAtDestination(const Position& currentPosition) const = 0;
    };
}
