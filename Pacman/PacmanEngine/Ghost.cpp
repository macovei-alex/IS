#include "Ghost.h"

#include "HuntPathFinder.h"


namespace pac
{
	Ghost::Ghost(Position initialPosition, State initialState)
		: mCurrentPosition(initialPosition)
	{
		SetState(initialState);
	}

	void Ghost::Update(const Maze& maze, const Pacman& pacman)
	{
		static Position lastPacmanPosition = pacman.GetCurrentPosition();

		// Wait for Pacman to move before updating
		if (pacman.GetCurrentPosition() != lastPacmanPosition)
		{
			mCurrentPosition = mPathFinder->NextMove(maze, pacman);
			lastPacmanPosition = pacman.GetCurrentPosition();
		}
	}
 
	void Ghost::Draw(IWindow* window) const
	{
		window->DrawTexture(mCurrentPosition, Textures::Ghost);
	}

	Position Ghost::GetCurrentPosition() const
	{
		return mCurrentPosition;
	}

	void Ghost::SetState(Ghost::State state)
	{
		mCurrentState = state;
		mPathFinder = std::make_unique<HuntPathFinder>(this);
	}
}

