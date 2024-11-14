#include "Maze.h"

#include <stdexcept>
#include <format>


pac::Maze::Maze() :
	mGhostSpawn(pac::Position::Invalid()),
	mPacmanSpawn(pac::Position::Invalid())
{
	// empty
}

void pac::Maze::InitCells(std::vector<std::vector<pac::CellType>>&& cells)
{
	mCells = std::move(cells);

	for (size_t row = 0; row < mCells.size(); ++row)
	{
		for (size_t col = 0; col < mCells[row].size(); ++col)
		{
			if (mCells[row][col] == CellType::GhostSpawn)
			{
				if (!mGhostSpawn.IsInvalid())
				{
					throw std::runtime_error(std::format(
						"Multiple ghost spawns found: ( {}, {} ) and ( {}, {} )",
						mGhostSpawn.row, mGhostSpawn.col, row, col));
				}
				mGhostSpawn = { (uint16_t)row, (uint16_t)col };
			}
			else if (mCells[row][col] == CellType::PacmanSpawn)
			{
				if (!mPacmanSpawn.IsInvalid())
				{
					throw std::runtime_error(std::format(
						"Multiple pacman spawns found: ( {}, {} ) and ( {}, {} )",
						mPacmanSpawn.row, mPacmanSpawn.col, row, col));
				}
				mPacmanSpawn = { (uint16_t)row, (uint16_t)col };
			}
		}
	}
}

pac::CellType pac::Maze::GetCellType(Position pos) const
{
	if (pos.row >= mCells.size() || pos.col >= mCells[0].size())
	{
		throw std::runtime_error(std::format("Position ( {}, {} ) out of range", pos.row, pos.col));
	}

	return mCells[pos.row][pos.col];
}

void pac::Maze::EatCell(Position pos)
{
	if (pos.row >= mCells.size() || pos.col >= mCells[0].size())
	{
		throw std::runtime_error(std::format("Position ( {}, {} ) out of range", pos.row, pos.col));
	}

	if (mCells[pos.row][pos.col] != CellType::Coin && mCells[pos.row][pos.col] != CellType::PowerUp)
	{
		throw std::runtime_error(std::format("Cell at ( {}, {} ) is not a coin or power-up", pos.row, pos.col));
	}

	mCells[pos.row][pos.col] = CellType::Empty;
}

pac::Position pac::Maze::GetGhostSpawnPosition() const
{
	if (mGhostSpawn.IsInvalid())
	{
		throw std::runtime_error("No ghost spawn found. You must call InitCells() before using the maze");
	}

	return mGhostSpawn;
}

pac::Position pac::Maze::GetPacmanSpawnPosition() const
{
	if (mPacmanSpawn.IsInvalid())
	{
		throw std::runtime_error("No pacman spawn found. You must call InitCells() before using the maze");
	}

	return mPacmanSpawn;
}