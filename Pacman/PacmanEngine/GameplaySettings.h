#pragma once

#include "typedefs.h"


namespace pac
{
	struct GameplaySettings
	{
		TickType mTicksPerSecond = 2;
		TickType mPacmanTicksPerMove = 2;
		TickType mGhostTicksPerMove = 2;
		TickType mGhostFearedTicksPerMove = 3;
		TickType mPowerUpDuration = 3000;
		ScoreType mScorePerCoin = 100;
		ScoreType mScorePerPowerUp = 500;
		uint8_t ghostCount = 1;
		TickType mGhostInitialSpawnDelay = 10;
		TickType mGhostRespawnDelay = 10;
	};
}
