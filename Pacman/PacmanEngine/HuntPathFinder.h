#pragma once

#include "IPathFinder.h"
#include "Ghost.h"

#include <stack>


namespace pac
{
	class HuntPathFinder : public IPathFinder
	{
	public:
		HuntPathFinder(Ghost* ghost);
		Position NextMove(const Maze& maze, const Pacman& pacman) override;

	private:
		void UpdatePath(const Maze& maze, const Pacman& pacman);

	private:
		Ghost* mGhost;
		Position mLastPacmanPosition;
		std::stack<Position> mPath;
	};
}
