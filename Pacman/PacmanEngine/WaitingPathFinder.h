#pragma once

#include "IPathFinder.h"
#include "Ghost.h"


namespace pac
{
	class WaitingPathFinder : public IPathFinder
	{
	public:
		WaitingPathFinder(const Ghost* ghost, TickType delay);
		Position NextMove(const Maze& maze, const Pacman& pacman) override;
		void AttachTo(const Ghost* ghost) override;

	private:
		const Ghost* mGhost;
		TickType mTargetTick;
	};
}
