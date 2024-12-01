#pragma once

#include "typedefs.h"


namespace pac
{
	struct GameplaySettings
	{
		TickType mTicksPerSecond = 5;

		ScoreType mScorePerCoin = 100;
		ScoreType mScorePerPowerUp = 500;
		ScoreType mScorePerGhost = 1000;

		TickType mPowerUpDuration = 10;

		TickType mPacmanTicksPerMove = 2;

		uint8_t mGhostCount = 1;

		TickType mGhostTicksPerMove = 2;
		TickType mGhostScaredTicksPerMove = 3;
		TickType mGhostInitialSpawnDelay = 15;
		TickType mGhostRespawnDelay = 15;
	};
}
