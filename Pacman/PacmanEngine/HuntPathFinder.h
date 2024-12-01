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
		void AttachTo(const Ghost* ghost) override;

	private:
		const Ghost* mGhost;
		Position mLastPacmanPosition;
		std::vector<Position> mPath;
	};
}
