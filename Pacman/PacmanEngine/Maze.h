#pragma once

#include "IWindow.h"
#include "Dimensions.h"

#include <memory>


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
		bool IsWalkable(Position pos) const;
		bool IsValid() const;
		void EatCell(Position pos);
		Position GetGhostSpawnPosition() const;
		Position GetPacmanSpawnPosition() const;
		Dimensions GetDimensions() const;
		bool SeeEachOther(Position p1, Position p2) const;
		void ReadMazeFromFile(std::string_view filename);
		void Draw(IWindow* window) const;

	private:
		std::vector<std::vector<CellType>> mCells;
		Position mGhostSpawn;
		Position mPacmanSpawn;
	};
}