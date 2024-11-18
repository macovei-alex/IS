#pragma once

#include <cstdint>


namespace pac
{
	struct GameplaySettings
	{
		uint16_t mTicksPerSecond = 6;
		uint16_t mPacmanTicksPerMove = 2;
		uint16_t mGhostTicksPerMove = 2;
		uint16_t mGhostFearedTicksPerMove = 3;
	};
}
