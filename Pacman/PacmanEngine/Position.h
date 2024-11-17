#pragma once


#include "Dimensions.h"

#include <limits>


namespace pac
{
	struct Position
	{
		decltype(Dimensions::rows) row = 0;
		decltype(Dimensions::cols) col = 0;

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