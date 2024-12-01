#pragma once

#include <cstdint>
#include <limits>


namespace pac
{
	struct Dimensions
	{
		PosType rows = 0;
		PosType cols = 0;

		static Dimensions GetInvalid()
		{
			return {
				std::numeric_limits<PosType>::max(),
				std::numeric_limits<PosType>::max()
			};
		}

		bool IsValid() const
		{
			return rows != std::numeric_limits<PosType>::max()
				&& cols != std::numeric_limits<PosType>::max();
		}
	};
}