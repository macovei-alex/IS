#pragma once

#include "Position.h"
#include "IPathFinder.h"
#include "Maze.h"
#include "Pacman.h"
#include "Textures.h"


namespace pac
{
	class Ghost
	{
	public:
		enum class State : uint8_t
		{
			Hunting,
			Scared
		};

	public:
		Ghost(Position initialPosition, State initialState);
		void Update(const Maze& maze, const Pacman& pacman);
		void Draw(IWindow* window) const;
		Position GetCurrentPosition() const;
		void SetState(State state);

	private:
		Position mCurrentPosition;
		std::unique_ptr<IPathFinder> mPathFinder;
		State mCurrentState;
	};
}
