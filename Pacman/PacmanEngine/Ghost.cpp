#include "Ghost.h"

#include "HuntPathFinder.h"
#include "ScaredPathFinder.h"
#include "RoamingPathFinder.h"
#include "DelayedRoamingPathFinder.h"

#include <format>


namespace pac
{
	Ghost::Ghost(Position initialPosition, TickType firstSpawnDelay, TickType respawnDelay)
		: mPosition(initialPosition)
		, mInitialPosition(initialPosition)
		, mTick(0)
		, mFirstSpawnDelay(firstSpawnDelay)
		, mRespawnDelay(respawnDelay)
	{
		SetState(State::Dead);
	}

	void Ghost::NextTick(const Maze& maze, const Pacman& pacman)
	{
		++mTick;
		if (mTick < mFirstSpawnDelay)
		{
			return;
		}

		mPosition = mPathFinder->NextMove(maze, pacman);
	}

	void Ghost::Draw(IWindow* window) const
	{
		window->DrawTexture(mPosition, Textures::Ghost);
		//daca ghost e in stare de eaten,fantoma dispare 3 secunde si reapare
		if (mState == State::Dead)
		{
			//window->DrawTexture(mPosition, Textures::Empty);
		}
	}

	Position Ghost::GetPosition() const
	{
		return mPosition;
	}

	void Ghost::SetState(State state)
	{
		mState = state;
		switch (mState)
		{
		case State::Hunting:
			mPathFinder = std::make_unique<HuntPathFinder>(this);
			break;
		case State::Scared:
			mPathFinder = std::make_unique<ScaredPathFinder>();
			break;
		case State::Roaming:
			mPathFinder = std::make_unique<RoamingPathFinder>(this);
			break;
		case State::Dead:
			mPathFinder = std::make_unique<DelayedRoamingPathFinder>(this, mRespawnDelay);
			mPosition = mInitialPosition;
			break;
		default:
			throw std::runtime_error(std::format("State ( {} ) does not exist", (int)state));
		}
	}

	pac::Ghost::State pac::Ghost::GetState() const
	{
		return mState;
	}
}
