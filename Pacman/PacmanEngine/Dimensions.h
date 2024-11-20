#pragma once

#include <cstdint>
#include <limits>


namespace pac
{
	struct Dimensions
	{
		uint16_t rows = 0;
		uint16_t cols = 0;

		static Dimensions GetInvalid()
		{
			return {
				std::numeric_limits<decltype(rows)>::max(),
				std::numeric_limits<decltype(cols)>::max()
			};
		}

		bool IsValid() const
		{
			return rows != std::numeric_limits<decltype(rows)>::max()
				&& cols != std::numeric_limits<decltype(cols)>::max();
		}
	};
}