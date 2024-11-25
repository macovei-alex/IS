#pragma once

#include "RoamingPathFinder.h"


namespace pac
{
	class DelayedRoamingPathFinder : public RoamingPathFinder
	{
	public:
		DelayedRoamingPathFinder(Ghost* ghost, TickType delay);
		Position NextMove(const Maze& maze, const Pacman& pacman) override;

	private:
		TickType mTick;
		TickType mDelay;
	};
}
