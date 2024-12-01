#pragma once

#include "IPathFinder.h"
#include "Ghost.h"


namespace pac
{
	class RoamingPathFinder : public IPathFinder
	{
	public:
		RoamingPathFinder(const Ghost* ghost);
		Position NextMove(const Maze& maze, const Pacman& pacman) override;
		void AttachTo(const Ghost* ghost) override;

	private:
		const Ghost* mGhost;
		std::vector<Position> mPath;
		Direction mCurrentDirection;
	};
}