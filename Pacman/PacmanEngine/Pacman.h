#pragma once

#include "Position.h"
#include "IListener.h"
#include "Maze.h"
#include "GameplaySettings.h"


namespace pac
{
	struct Direction
	{
		int8_t row = 0;
		int8_t col = 0;

		static Direction GetInvalid() { return { 0, 0 }; }

		inline bool IsValid() const { return row != 0 || col != 0; }
	};

	class Pacman : public IListener
	{
	public:
		Pacman(Position initialPosition, decltype(GameplaySettings::mPacmanTicksPerMove) ticksPerMove);
		void TryMove(const Maze& maze);
		Position GetCurrentPosition() const;
		decltype(GameplaySettings::mPacmanTicksPerMove) GetTicksPerMove() const;
		void Draw(IWindow* window) const;
		void OnEvent(IEvent* event) override;

	private:
		Position mCurrentPosition;
		Direction mCurrentDirection;
		Direction mNextDirection;
		decltype(GameplaySettings::mPacmanTicksPerMove) mTicksSinceLastMove;
		decltype(GameplaySettings::mPacmanTicksPerMove) mTicksPerMove;
	};
}