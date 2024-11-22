#pragma once

#include "PacmanEngine/Maze.h"

#include <string_view>


namespace pac::test
{
	pac::Maze ReadMazeFromStr(std::string_view str);
}
