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

	protected:
		const Ghost* mGhost;
		Direction mCurrentDirection;
	};
}