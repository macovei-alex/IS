#pragma once

#include "IWindow.h"
#include "Dimensions.h"
#include "GameplaySettings.h"

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
		void InitScores(ScoreType coinScore, ScoreType powerUpScore);
		void InitCells(std::vector<std::vector<CellType>>&& cells);
		CellType GetCellType(Position pos) const;
		bool IsWalkable(Position pos) const;
		bool IsValid() const;
		uint64_t EatCell(Position pos);
		Position GetGhostSpawnPosition() const;
		Position GetPacmanSpawnPosition() const;
		Dimensions GetDimensions() const;
		bool SeeEachOther(Position p1, Position p2) const;
		void ReadMazeFromFile(std::string_view filename);
		void Draw(IWindow* window) const;
		bool HasWonGame();

	private:
		std::vector<std::vector<CellType>> mCells;
		Position mGhostSpawn;
		Position mPacmanSpawn;
		ScoreType mCoinScore;
		ScoreType mPowerUpScore;
	};
}