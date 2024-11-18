#pragma once

#include "Position.h"
#include "KeyCode.h"
#include "IListener.h"
#include "Maze.h"

namespace pac
{
	enum class Direction : uint8_t
	{
		Up,
		Down,
		Left,
		Right,
		Unknown
	};

	class Pacman : public IListener
	{
	public:
		Pacman(uint16_t ticksPerMove);
		void TryMove(const Maze& maze);
		Position GetCurrentPosition();
		void OnEvent(std::shared_ptr<IEvent> event) override;

	private:
		Position mCurrentPosition;
		Direction mCurrentDirection;
		Direction mNextDirection;
		uint16_t mTicksSinceLastMove;
		uint16_t mTicksPerMove;
	};
}