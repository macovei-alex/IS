#pragma once

#include "Position.h"

#include <vector>


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

		static const std::vector<Direction>& AllDirections()
		{
			static const std::vector<Direction> directions = {
				Direction::Up(), Direction::Down(), Direction::Left(), Direction::Right()
			};
			return directions;
		}

		bool operator==(Direction other) const
		{
			return row == other.row
				&& col == other.col;
		}

		Direction Opposite() const
		{
			return { static_cast<decltype(row)>(-row), static_cast<decltype(col)>(-col) };
		}
	};

	inline Position Add(Position pos, Direction dir)
	{
		return {
			static_cast<PosType>(pos.row + dir.row),
			static_cast<PosType>(pos.col + dir.col)
		};
	}
}
