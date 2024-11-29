#pragma once

#include "IPathFinder.h"
#include "Ghost.h"

#include <stack>


namespace pac
{
	class HuntPathFinder : public IPathFinder
	{
	public:
		HuntPathFinder(const Ghost* ghost);
		Position NextMove(const Maze& maze, const Pacman& pacman) override;
		void Attach(Ghost* ghost) override;

	private:
		void UpdatePath(const Maze& maze, const Pacman& pacman);

	private:
		const Ghost* mGhost;
		Position mLastPacmanPosition;
		std::stack<Position> mPath;
	};
}
