#include "Ghost.h"

#include "HuntPathFinder.h"
#include "ScaredPathFinder.h"
#include "RoamingPathFinder.h"
#include "WaitingPathFinder.h"

#include <format>


namespace pac
{
	Ghost::Ghost(Position spawnPos, TickType firstSpawnDelay, const GameplaySettings& settings)
		: mPosition(spawnPos)
		, mSpawnPosition(spawnPos)
		, mTick(0)
		, mTicksPerMove(settings.mGhostTicksPerMove)
		, mTicksPerMoveScared(settings.mGhostScaredTicksPerMove)
		, mFirstSpawnDelay(firstSpawnDelay)
		, mRespawnDelay(settings.mGhostRespawnDelay)
	{
		SetState(State::Roaming);

		// not necessary
		mPathFinder->AttachTo(this);
	}

	Ghost::Ghost(Ghost&& other) noexcept
		: mPosition(other.mPosition)
		, mSpawnPosition(other.mSpawnPosition)
		, mTick(other.mTick)
		, mTicksPerMove(other.mTicksPerMove)
		, mTicksPerMoveScared(other.mTicksPerMoveScared)
		, mFirstSpawnDelay(other.mFirstSpawnDelay)
		, mRespawnDelay(other.mRespawnDelay)
		, mPathFinder(std::move(other.mPathFinder))
		, mState(other.mState)
	{
		// !!! VERY IMPORTANT !!!
		// for moving the ghost into the ghosts vector without breaking
		// the pathFinder's pointer to the ghost
		mPathFinder->AttachTo(this);
	}

	void Ghost::NextTick(const Maze& maze, const Pacman& pacman)
	{
		++mTick;
		if (mTick < mFirstSpawnDelay)
		{
			return;
		}

		if (!((mState != State::Scared && mTick % mTicksPerMove == 0
			|| mState == State::Scared && mTick % mTicksPerMoveScared == 0)))
		{
			return;
		}

		auto nextPos = mPathFinder->NextMove(maze, pacman);
		if (mState == State::Dead && nextPos == Position::GetInvalid())
		{
			if (pacman.IsPoweredUp())
			{
				SetState(State::Scared);
			}
			else
			{
				SetState(State::Roaming);
			}
			nextPos = mPathFinder->NextMove(maze, pacman);
		}
		mPosition = nextPos;
	}

	void Ghost::Draw(IWindow* window) const
	{
		if (mState == State::Dead)
		{
			// TODO: fix this after testing
			window->DrawTexture(mPosition, Textures::DeadGhost);
			return;
		}
		else if (mState == State::Scared)
		{
			window->DrawTexture(mPosition, Textures::ScaredGhost);
		}
		else
		{
			window->DrawTexture(mPosition, Textures::Ghost);
		}
	}

	Position Ghost::GetPosition() const
	{
		return mPosition;
	}

	void Ghost::SetState(State state)
	{
		if (mState == state)
		{
			return;
		}

		mState = state;
		switch (mState)
		{
		case State::Hunting:
			mPathFinder = std::make_unique<HuntPathFinder>(this);
			break;
		case State::Scared:
			mPathFinder = std::make_unique<ScaredPathFinder>(this);
			break;
		case State::Roaming:
			mPathFinder = std::make_unique<RoamingPathFinder>(this);
			break;
		case State::Dead:
			mPathFinder = std::make_unique<WaitingPathFinder>(this, mRespawnDelay);
			mPosition = mSpawnPosition;
			break;
		default:
			throw std::runtime_error(std::format("State ( {} ) does not exist", (int)state));
		}
	}

	Ghost::State Ghost::GetState() const
	{
		return mState;
	}

	TickType Ghost::GetTick() const
	{
		return mTick;
	}
}
