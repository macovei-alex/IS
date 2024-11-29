#pragma once

#include "IPathFinder.h"
#include "Ghost.h"

namespace pac
{
	class ScaredPathFinder : public IPathFinder
	{
	public:
		ScaredPathFinder(const Ghost* ghost);
		Position NextMove(const Maze& maze, const Pacman& pacman) override;
		void AttachTo(const Ghost* ghost) override;

	private:
		const Ghost* mGhost;
	};
}
