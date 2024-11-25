#pragma once

#include "typedefs.h"


namespace pac
{
	struct GameplaySettings
	{
		TickType mTicksPerSecond = 6;
		TickType mPacmanTicksPerMove = 2;
		TickType mGhostTicksPerMove = 2;
		TickType mGhostFearedTicksPerMove = 3;
		TickType mPowerUpDuration = 30;
		ScoreType mScorePerCoin = 100;
		ScoreType mScorePerPowerUp = 500;
		uint8_t ghostCount = 1;
		TickType mGhostFirstSpawnDelay = 10;
	};
}
