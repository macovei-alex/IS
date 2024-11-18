#pragma once

#include "IPathFinder.h"
#include <queue>
#include <unordered_set>

namespace pac
{
    class PathFinder : public IPathFinder
    {
    public:
        PathFinder();
        void SetDestination(const Position& destination) override;
        Position NextMove(const Position& currentPosition, const Maze& maze) override;
        bool IsAtDestination(const Position& currentPosition) const override;

    private:
        Position destination; 
        //std::vector<Position> CalculatePath(const Position& start, const Position& end, const Maze& maze);

    };
}
