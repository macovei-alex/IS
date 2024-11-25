#pragma once

#include "IPathFinder.h"
#include "Ghost.h"



namespace pac
{
	class RoamingPathFinder : public IPathFinder
	{
	public:
		RoamingPathFinder(Ghost* ghost);
		Position NextMove(const Maze& maze, const Pacman& pacman) override;

	private:
		Ghost* mGhost;
	};
}