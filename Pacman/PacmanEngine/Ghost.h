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
			Scared,
			Roaming,
			Eaten
		};

	public:
		Ghost(Position initialPosition, TickType firstSpawnDelay);
		void NextTick(const Maze& maze, const Pacman& pacman);
		void Draw(IWindow* window) const;
		Position GetCurrentPosition() const;
		void SetState(State state);
		State GetState() const;
		
	private:
		Position mPosition;
		TickType mFirstSpawnDelay;
		std::unique_ptr<IPathFinder> mPathFinder;
		State mState;
		const Position mInitialPosition;
	};
}
