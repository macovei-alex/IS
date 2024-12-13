#pragma once

#include "typedefs.h"
#include <limits>
#include <utility>

namespace pac
{
	/**
  * @struct Position
  * @brief Represents a position in a grid or maze.
  */
	struct Position
	{
		PosType row = 0; ///< Row position.
		PosType col = 0; ///< Column position.

		/**
   * @brief Gets an invalid position.
   * @return An invalid Position object.
   */
		static Position GetInvalid()
		{
			return {
				std::numeric_limits<PosType>::max(),
				std::numeric_limits<PosType>::max()
			};
		}

		/**
   * @brief Checks if the position is valid.
   * @return True if the position is valid, false otherwise.
   */
		bool IsValid() const
		{
			return row != std::numeric_limits<PosType>::max() &&
				col != std::numeric_limits<PosType>::max();
		}

		/**
   * @brief Equality operator for Position.
   * @param other The other Position to compare.
   * @return True if the positions are equal, false otherwise.
   */
		bool operator==(const Position& other) const
		{
			return row == other.row && col == other.col;
		}

		/**
   * @brief Inequality operator for Position.
   * @param other The other Position to compare.
   * @return True if the positions are not equal, false otherwise.
   */
		bool operator!=(const Position& other) const
		{
			return !(*this == other);
		}

		/**
   * @brief Less-than operator for Position.
   * @param other The other Position to compare.
   * @return True if this position is less than the other, false otherwise.
   */
		bool operator<(const Position& other) const
		{
			if (row != other.row)
				return row < other.row;
			return col < other.col;
		}

		/**
   * @brief Calculates the number of cells to another position.
   * @param other The other position.
   * @return The number of cells to the other position.
   */
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
