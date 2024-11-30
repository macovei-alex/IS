#pragma once

#include <cstdint>


namespace pac
{
	enum class Textures : uint8_t
	{
		Wall,
		Pacman,
		Ghost,
		ScaredGhost,
		DeadGhost,
		Coin,
		PowerUp,
		_Count
	};
}
