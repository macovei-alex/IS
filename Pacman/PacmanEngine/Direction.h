#pragma once

#include "Position.h"
#include <vector>

namespace pac
{
	/**
  * @struct Direction
  * @brief Represents a direction in a grid or maze.
  */
	struct Direction
	{
		int8_t row = 0; ///< Row direction.
		int8_t col = 0; ///< Column direction.

		/**
   * @brief Gets an invalid direction.
   * @return An invalid Direction object.
   */
		static constexpr Direction GetInvalid() { return { 0, 0 }; }

		/**
   * @brief Checks if the direction is valid.
   * @return True if the direction is valid, false otherwise.
   */
		inline bool IsValid() const { return row != 0 || col != 0; }

		/**
   * @brief Gets the upward direction.
   * @return The upward Direction object.
   */
		static constexpr Direction Up() { return { -1, 0 }; }

		/**
   * @brief Gets the downward direction.
   * @return The downward Direction object.
   */
		static constexpr Direction Down() { return { 1, 0 }; }

		/**
   * @brief Gets the leftward direction.
   * @return The leftward Direction object.
   */
		static constexpr Direction Left() { return { 0, -1 }; }

		/**
   * @brief Gets the rightward direction.
   * @return The rightward Direction object.
   */
		static constexpr Direction Right() { return { 0, 1 }; }

		/**
   * @brief Gets all possible directions.
   * @return A vector of all possible Direction objects.
   */
		static const std::vector<Direction>& AllDirections()
		{
			static const std::vector<Direction> directions = {
				Direction::Up(), Direction::Down(), Direction::Left(), Direction::Right()
			};
			return directions;
		}

		/**
   * @brief Equality operator for Direction.
   * @param other The other Direction to compare.
   * @return True if the directions are equal, false otherwise.
   */
		bool operator==(Direction other) const
		{
			return row == other.row
				&& col == other.col;
		}

		/**
   * @brief Gets the opposite direction.
   * @return The opposite Direction object.
   */
		Direction Opposite() const
		{
			return { static_cast<decltype(row)>(-row), static_cast<decltype(col)>(-col) };
		}
	};

	/**
  * @brief Adds a direction to a position.
  * @param pos The position.
  * @param dir The direction.
  * @return The new position after adding the direction.
  */
	inline Position Add(Position pos, Direction dir)
	{
		return {
			static_cast<PosType>(pos.row + dir.row),
			static_cast<PosType>(pos.col + dir.col)
		};
	}
}
