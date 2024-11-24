#pragma once

#include "IListener.h"
#include "Maze.h"
#include "GameplaySettings.h"
#include "Direction.h"


namespace pac
{
	class Pacman : public IListener
	{
	public:
		Pacman(Position initialPosition, TicksType ticksPerMove, TicksType powerUpDuration);
		void TryMove(Maze& maze);
		Position GetCurrentPosition() const;
		void IncreaseScore(ScoreType value);
		ScoreType GetScore() const;
		void SetPowerUp();
		bool IsPoweredUp() const;
		void Draw(IWindow* window) const;
		void OnEvent(IEvent* event) override;

	private:
		Position mPosition;
		Direction mDirection;
		Direction mNextDirection;
		TicksType mTick;
		TicksType mTicksPerMove;
		ScoreType mScore;
		TicksType mLastPowerUpStart;

	private:
		const TicksType mPowerUpDuration;
	};
}