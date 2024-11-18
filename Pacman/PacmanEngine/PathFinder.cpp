#include "PathFinder.h"
using namespace pac;
PathFinder::PathFinder()
{
	//constructor , to be implemented later
}

void PathFinder::SetDestination(const Position& destination)
{
}

Position PathFinder::NextMove(const Position& currentPosition, const Maze& maze)
{
	return Position();
}

bool PathFinder::IsAtDestination(const Position& currentPosition) const
{
	return false;
}

//std::vector<Position> PathFinder::CalculatePath(const Position& start, const Position& end, const Maze& maze)
//{
//	return std::vector<Position>();
//}


