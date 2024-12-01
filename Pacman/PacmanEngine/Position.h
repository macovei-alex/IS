#pragma once

#include "typedefs.h"

#include <limits>
#include <utility>


namespace pac
{
	struct Position
	{
		PosType row = 0;
		PosType col = 0;

		static Position GetInvalid()
		{
			return {
				std::numeric_limits<PosType>::max(),
				std::numeric_limits<PosType>::max()
			};
		}

		bool IsValid() const
		{
			return row != std::numeric_limits<PosType>::max() &&
				col != std::numeric_limits<PosType>::max();
		}

		bool operator==(const Position& other) const
		{
			return row == other.row && col == other.col;
		}

		bool operator!=(const Position& other) const
		{
			return !(*this == other);
		}
		bool operator<(const Position& other) const
		{
			if (row != other.row)
				return row < other.row;
			return col < other.col;
		}



		PosType NumberOfCellsTo(Position other) const
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
