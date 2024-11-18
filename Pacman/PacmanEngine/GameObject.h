#pragma once

#include "Position.h"

namespace pac
{
	enum class Direction : uint8_t
	{
		Up,
		Down,
		Left,
		Right
	};

	class GameObject
	{
	public:
		GameObject();
		uint64_t GetTicksSinceLastMove();
		Position GetPosition();
		Direction GetDirection();

	private:
		Position position;
		Direction direction;
		uint64_t ticksSinceLastMove;
	};
}