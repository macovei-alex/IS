#pragma once

#include <cstdint>
#include <limits>

namespace pac
{
	struct Position
	{
		uint16_t row = 0;
		uint16_t col = 0;

		inline static Position Invalid()
		{
			return {
				std::numeric_limits<decltype(row)>::max(),
				std::numeric_limits<decltype(col)>::max()
			};
		}

		inline bool IsInvalid() const
		{
			return row == std::numeric_limits<decltype(row)>::max()
				&& col == std::numeric_limits<decltype(col)>::max();
		}
	};
}