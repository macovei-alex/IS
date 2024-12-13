#pragma once

#include <cstdint>
#include <limits>

namespace pac
{
	/**
  * @struct Dimensions
  * @brief Represents the dimensions of a grid or maze.
  */
	struct Dimensions
	{
		PosType rows = 0; ///< Number of rows.
		PosType cols = 0; ///< Number of columns.

		/**
   * @brief Gets an invalid Dimensions object.
   * @return A Dimensions object with invalid values.
   */
		static Dimensions GetInvalid()
		{
			return {
				std::numeric_limits<PosType>::max(),
				std::numeric_limits<PosType>::max()
			};
		}

		/**
   * @brief Checks if the dimensions are valid.
   * @return True if the dimensions are valid, false otherwise.
   */
		bool IsValid() const
		{
			return rows != std::numeric_limits<PosType>::max()
				&& cols != std::numeric_limits<PosType>::max();
		}
	};
}