#pragma once

#include <vector>
#include <string>
#include "Position.h"


namespace pac
{
	enum class CellType : uint8_t
	{
		Empty,
		Wall,
		Coin,
		PowerUp,
		GhostSpawn,
		PacmanSpawn
	};

	class Maze
	{
	public:
		Maze();
		void InitCells(std::vector<std::vector<CellType>>&& cells);
		CellType GetCellType(Position pos) const;
		void EatCell(Position pos);
		Position GetGhostSpawnPosition() const;
		Position GetPacmanSpawnPosition() const;
		std::tuple<int, int> GetSize() const;
		void ReadMazeFromFile(const std::string& filename);
	private:
		std::vector<std::vector<CellType>> mCells;
		Position mGhostSpawn;
		Position mPacmanSpawn;
	};
}