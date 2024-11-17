#pragma once

#include <cstdint>


namespace pac
{
	struct GameplaySettings
	{
		uint16_t ticksPerSecond;
		uint8_t ghostMoveTicks;
		uint8_t ghostFearedMoveTicks;
	};
}
