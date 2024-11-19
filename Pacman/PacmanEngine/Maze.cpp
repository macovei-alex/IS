#include "Maze.h"

#include <stdexcept>
#include <format>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>


pac::Maze::Maze()
	: mGhostSpawn(pac::Position::GetInvalid())
	, mPacmanSpawn(pac::Position::GetInvalid())
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
				if (mGhostSpawn.IsValid())
				{
					throw std::runtime_error(std::format(
						"Multiple ghost spawns found: ( {}, {} ) and ( {}, {} )",
						mGhostSpawn.row, mGhostSpawn.col, row, col));
				}
				mGhostSpawn = {
					static_cast<decltype(Position::row)>(row),
					static_cast<decltype(Position::row)>(col)
				};
			}
			else if (mCells[row][col] == CellType::PacmanSpawn)
			{
				if (mPacmanSpawn.IsValid())
				{
					throw std::runtime_error(std::format(
						"Multiple pacman spawns found: ( {}, {} ) and ( {}, {} )",
						mPacmanSpawn.row, mPacmanSpawn.col, row, col));
				}
				mPacmanSpawn = {
					static_cast<decltype(Position::row)>(row),
					static_cast<decltype(Position::row)>(col)
				};
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
	if (!mGhostSpawn.IsValid())
	{
		throw std::runtime_error("No ghost spawn found. You must call InitCells() or ReadFromFile() before using the maze");
	}

	return mGhostSpawn;
}

pac::Position pac::Maze::GetPacmanSpawnPosition() const
{
	if (!mPacmanSpawn.IsValid())
	{
		throw std::runtime_error("No pacman spawn found. You must call InitCells() or ReadFromFile() before using the maze");
	}

	return mPacmanSpawn;
}

pac::Dimensions pac::Maze::GetDimensions() const
{
	if (mCells.size() == 0)
	{
		return {};
	}

	return {
		static_cast<decltype(Dimensions::rows)>(mCells.size()),
		static_cast<decltype(Dimensions::cols)>(mCells[0].size())
	};
}

void pac::Maze::ReadMazeFromFile(std::string_view filename)
{
	std::ifstream file(filename.data());
	std::stringstream filetream;
	filetream << file.rdbuf();
	file.close();

	std::string line;
	std::vector<std::vector<CellType>> cells;

	while (std::getline(filetream, line))
	{
		std::vector<pac::CellType> row;
		std::istringstream lineStream(line);
		int value;

		while (lineStream >> value)
		{
			switch (value)
			{
			case (int)CellType::Empty: row.push_back(CellType::Empty); break;
			case (int)CellType::Wall: row.push_back(CellType::Wall); break;
			case (int)CellType::Coin: row.push_back(CellType::Coin); break;
			case (int)CellType::PowerUp: row.push_back(CellType::PowerUp); break;
			case (int)CellType::PacmanSpawn: row.push_back(CellType::PacmanSpawn); break;
			case (int)CellType::GhostSpawn: row.push_back(CellType::GhostSpawn); break;
			default: throw std::runtime_error(std::format("Invalid cell value ( {} )", value));
			}
		}

		cells.push_back(std::move(row));
	}

	InitCells(std::move(cells));
}

void pac::Maze::DrawMaze(IWindow* window) const
{
	auto [height, width] = GetDimensions();

	Position position;

	for (; position.row < height; ++position.row) {
		for (position.col = 0; position.col < width; ++position.col) {
			switch (GetCellType(position))
			{
			case CellType::Wall:
				window->DrawTexture(position, Textures::Wall);
				break;
			case CellType::Coin:
				window->DrawTexture(position, Textures::Coin);
				break;
			case CellType::PowerUp:
				window->DrawTexture(position, Textures::PowerUp);
				break;
			default:
				break;
			}
		}
	}
}