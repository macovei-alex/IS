#pragma once

#include "Position.h"
#include "IListener.h"
#include "Maze.h"
#include "GameplaySettings.h"
#include "Direction.h"


namespace pac
{
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