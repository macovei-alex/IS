#include "Ghost.h"

#include "HuntPathFinder.h"
#include "ScaredPathFinder.h"
#include "RoamingPathFinder.h"

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

		if (pacman.GetCurrentPosition() != lastPacmanPosition)
		{
			mPosition = mPathFinder->NextMove(maze, pacman);
			lastPacmanPosition = pacman.GetCurrentPosition();
		}
	}

	void Ghost::Draw(IWindow* window) const
	{
		window->DrawTexture(mPosition, Textures::Ghost);
		//daca ghost e in stare de eaten,fantoma dispare 3 secunde si reapare'
		if (mState == State::Eaten)
		{
			//window->DrawTexture(mPosition, Textures::Empty);
		}
		
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
		else if (state == State::Scared)
		{
			 mPathFinder = std::make_unique<ScaredPathFinder>();
		}
		else if (state == State::Roaming)
		{
			mPathFinder = std::make_unique<RoamingPathFinder>(this);
		}
	}

	pac::Ghost::State pac::Ghost::GetState() const
	{
		return mState;
	}




	

}
