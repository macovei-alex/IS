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
			Dead
		};

	public:
		Ghost(Position initialPosition, TickType firstSpawnDelay, TickType respawnDelay);
		void NextTick(const Maze& maze, const Pacman& pacman);
		void Draw(IWindow* window) const;
		Position GetPosition() const;
		void SetState(State state);
		State GetState() const;

	private:
		Position mPosition;
		TickType mTick;
		TickType mFirstSpawnDelay;
		TickType mRespawnDelay;
		std::unique_ptr<IPathFinder> mPathFinder;
		State mState;

	private:
		const Position mInitialPosition;
	};
}
