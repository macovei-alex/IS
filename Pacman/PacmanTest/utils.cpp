#include "utils.h"

#include <sstream>
#include <format>
#include <algorithm>


pac::Maze pac::test::ReadMazeFromStr(std::string_view str)
{
	std::stringstream filetream;
	filetream << str;

	std::string line;
	std::vector<std::vector<pac::CellType>> cells;

	while (std::getline(filetream, line))
	{
		if (line == "" || std::all_of(line.begin(), line.end(), [](char c) { return std::isblank(c); }))
		{
			continue;
		}

		std::vector<pac::CellType> row;
		std::istringstream lineStream(line);
		int value;

		while (lineStream >> value)
		{
			switch (value)
			{
			case (int)pac::CellType::Empty: row.push_back(pac::CellType::Empty); break;
			case (int)pac::CellType::Wall: row.push_back(pac::CellType::Wall); break;
			case (int)pac::CellType::Coin: row.push_back(pac::CellType::Coin); break;
			case (int)pac::CellType::PowerUp: row.push_back(pac::CellType::PowerUp); break;
			case (int)pac::CellType::PacmanSpawn: row.push_back(pac::CellType::PacmanSpawn); break;
			case (int)pac::CellType::GhostSpawn: row.push_back(pac::CellType::GhostSpawn); break;
			default: throw std::runtime_error(std::format("Invalid cell value ( {} )", value));
			}
		}

		cells.push_back(std::move(row));
	}

	pac::Maze maze;
	maze.InitCells(std::move(cells));
	return maze;
}
