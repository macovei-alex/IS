#pragma once

#include "IPathFinder.h"
#include "Ghost.h"


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
		std::vector<Position> mPath;
	};
}
