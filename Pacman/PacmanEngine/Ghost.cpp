#include "Ghost.h"

#include "HuntPathFinder.h"
#include "ScaredPathFinder.h"
#include "RoamingPathFinder.h"
#include "DelayedRoamingPathFinder.h"

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
		SetState(State::Dead);
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

		Position nextPosition = mPathFinder->NextMove(maze, pacman);
		if (nextPosition == mPosition)
		{
			for (Direction direction : Direction::AllDirections())
			{
				Position alternative = Add(mPosition, direction);
				if (maze.GetCellType(alternative) != CellType::Wall)
				{
					nextPosition = alternative;
					break;
				}
			}
		}

		mPosition = nextPosition;
	}

	void Ghost::Draw(IWindow* window) const
	{
		//daca ghost e in stare de eaten,fantoma dispare 3 secunde si reapare
		if (mState == State::Dead)
		{
			//window->DrawTexture(mPosition, Textures::Empty);
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
			mPathFinder = std::make_unique<DelayedRoamingPathFinder>(this, mRespawnDelay);
			mPosition = mSpawnPosition;
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
