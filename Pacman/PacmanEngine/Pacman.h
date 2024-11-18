#pragma once

#include "Position.h"
#include "KeyCode.h"
#include "IListener.h"

namespace pac
{
	enum class Direction : uint8_t
	{
		Up,
		Down,
		Left,
		Right
	};

	class Pacman : public IListener
	{
	public:
		Pacman();
		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();
		uint64_t GetTicksSinceLastMove();
		Position GetPosition();
		Direction GetDirection();

	private:
		Position currentPosition;
		KeyCode currentDirection;
		KeyCode nextDirection;
		Position position;
		Direction direction;
		uint64_t ticksSinceLastMove;
	};
}