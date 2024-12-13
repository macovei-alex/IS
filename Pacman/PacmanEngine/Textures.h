#pragma once

#include <cstdint>

namespace pac
{
	/**
  * @enum Textures
  * @brief Represents the different textures used in the game.
  */
	enum class Textures : uint8_t
	{
		Wall,        ///< Texture for walls.
		Pacman,      ///< Texture for Pacman.
		Ghost,       ///< Texture for ghosts.
		ScaredGhost, ///< Texture for scared ghosts.
		DeadGhost,   ///< Texture for dead ghosts.
		Coin,        ///< Texture for coins.
		PowerUp,     ///< Texture for power-ups.
		_Count       ///< Number of textures.
	};
}
