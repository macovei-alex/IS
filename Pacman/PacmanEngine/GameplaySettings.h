#pragma once

#include <cstdint>


namespace pac
{
	struct GameplaySettings
	{
		uint16_t mTicksPerSecond;
		uint16_t mPacmanTicksPerMove;
		uint16_t mGhostTicksPerMove;
		uint16_t mGhostFearedTicksPerMove;
	};
}
