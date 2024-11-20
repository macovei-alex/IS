#pragma once

#include "Dimensions.h"


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
			return row != std::numeric_limits<decltype(row)>::max()
				&& col != std::numeric_limits<decltype(col)>::max();
		}
	};
}