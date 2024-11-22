#pragma once

#include "Position.h"

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

	inline Position Add(Position pos, Direction dir)
	{
		return {
			static_cast<decltype(Position::row)>(pos.row + dir.row),
			static_cast<decltype(Position::col)>(pos.col + dir.col)
		};
	}
}
