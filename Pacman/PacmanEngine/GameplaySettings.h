#pragma once

#include "typedefs.h"

namespace pac
{
	/**
  * @struct GameplaySettings
  * @brief Holds the settings for the gameplay.
  */
	struct GameplaySettings
	{
		TickType mTicksPerSecond = 10; ///< Number of ticks per second.

		ScoreType mScorePerCoin = 100; ///< Score per coin collected.
		ScoreType mScorePerPowerUp = 500; ///< Score per power-up collected.
		ScoreType mScorePerGhost = 1000; ///< Score per ghost eaten.

		TickType mPowerUpDuration = 50; ///< Duration of power-up effect in ticks.

		TickType mPacmanTicksPerMove = 2; ///< Number of ticks per Pacman move.

		uint8_t mGhostCount = 4; ///< Number of ghosts in the game.

		TickType mGhostTicksPerMove = 2; ///< Number of ticks per ghost move.
		TickType mGhostScaredTicksPerMove = 3; ///< Number of ticks per ghost move when scared.
		TickType mGhostInitialSpawnDelay = 15; ///< Initial spawn delay for ghosts in ticks.
		TickType mGhostRespawnDelay = 15; ///< Respawn delay for ghosts in ticks.
	};
}
