#pragma once

#include "Position.h"

namespace pac
{
	struct Direction
	{
		int8_t row = 0;
		int8_t col = 0;

		static constexpr Direction GetInvalid() { return { 0, 0 }; }

		inline bool IsValid() const { return row != 0 || col != 0; }

		static constexpr Direction Up() { return { -1, 0 }; }
		static constexpr Direction Down() { return { 1, 0 }; }
		static constexpr Direction Left() { return { 0, -1 }; }
		static constexpr Direction Right() { return { 0, 1 }; }

		bool operator==(const Direction& other) const
		{
			return row == other.row
				&& col == other.col;
		}
	};

	inline Position Add(Position pos, Direction dir)
	{
		return {
			static_cast<decltype(Position::row)>(pos.row + dir.row),
			static_cast<decltype(Position::col)>(pos.col + dir.col)
		};
	}
}
