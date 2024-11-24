#include "Ghost.h"

#include "HuntPathFinder.h"


namespace pac
{
	Ghost::Ghost(Position initialPosition, TicksType firstSpawnDelay)
		: mPosition(initialPosition)
		, mFirstSpawnDelay(firstSpawnDelay)
	{
		SetState(State::Roaming);
	}

	void Ghost::NextTick(const Maze& maze, const Pacman& pacman)
	{
		static Position lastPacmanPosition = pacman.GetCurrentPosition();
		static TicksType tick = 0;

		++tick;
		if (tick < mFirstSpawnDelay)
		{
			return;
		}

		// Wait for Pacman to move before updating
		if (pacman.GetCurrentPosition() != lastPacmanPosition)
		{
			mPosition = mPathFinder->NextMove(maze, pacman);
			lastPacmanPosition = pacman.GetCurrentPosition();
		}
	}

	void Ghost::Draw(IWindow* window) const
	{
		window->DrawTexture(mPosition, Textures::Ghost);
	}

	Position Ghost::GetCurrentPosition() const
	{
		return mPosition;
	}

	void Ghost::SetState(State state)
	{
		mState = state;
		if (state == State::Hunting)
		{
			mPathFinder = std::make_unique<HuntPathFinder>(this);
		}
	}
}
