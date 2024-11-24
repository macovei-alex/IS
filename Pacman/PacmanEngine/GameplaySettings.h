#pragma once

#include <cstdint>


namespace pac
{
	using TicksType = uint16_t;
	using ScoreType = uint64_t;

	struct GameplaySettings
	{
		TicksType mTicksPerSecond = 6;
		TicksType mPacmanTicksPerMove = 2;
		TicksType mGhostTicksPerMove = 2;
		TicksType mGhostFearedTicksPerMove = 3;
		TicksType mPowerUpDuration = 30;
		ScoreType mScorePerCoin = 100;
		ScoreType mScorePerPowerUp = 500;
		uint8_t ghostCount = 1;
		TicksType mGhostFirstSpawnDelay = 10;
	};
}
