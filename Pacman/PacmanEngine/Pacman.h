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

		static Direction Up() { return { -1, 0 }; }
		static Direction Down() { return { 1, 0 }; }
		static Direction Left() { return { 0, -1 }; }
		static Direction Right() { return { 0, 1 }; }
	};

	Position Add(Position pos, Direction dir);

	class Pacman : public IListener
	{
	public:
		Pacman(Position initialPosition, decltype(GameplaySettings::mPacmanTicksPerMove) pacmanTicksPerMove);
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