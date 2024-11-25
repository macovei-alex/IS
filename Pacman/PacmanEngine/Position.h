#pragma once

#include "Dimensions.h"

#include <limits>
#include <utility>


namespace pac
{
	struct Position
	{
		decltype(Dimensions::rows) row = 0;
		decltype(Dimensions::cols) col = 0;

		static Position GetInvalid()
		{
			return {
				std::numeric_limits<decltype(row)>::max(),
				std::numeric_limits<decltype(col)>::max()
			};
		}

		bool IsValid() const
		{
			return row != std::numeric_limits<decltype(row)>::max() &&
				col != std::numeric_limits<decltype(col)>::max();
		}

		bool operator==(const Position& other) const
		{
			return row == other.row && col == other.col;
		}

		bool operator!=(const Position& other) const
		{
			return !(*this == other);
		}

		decltype(row) NumberOfCellsTo(Position other) const
		{
			Position max = {
				std::max(row, other.row),
				std::max(col, other.col)
			};
			Position min = {
				std::min(row, other.row),
				std::min(col, other.col)
			};
			return max.row - min.row + max.col - min.col;
		}
	};
}
