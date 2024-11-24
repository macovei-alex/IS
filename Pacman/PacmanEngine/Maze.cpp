#include "Maze.h"

#include "Logger/Logger.h"
#include "Direction.h"
#include "Pacman.h"

#include <format>
#include <iostream>
#include <fstream>
#include <sstream>


pac::Maze::Maze()
	: mGhostSpawn(pac::Position::GetInvalid())
	, mPacmanSpawn(pac::Position::GetInvalid())
{
	// empty
}

void pac::Maze::InitCells(std::vector<std::vector<pac::CellType>>&& cells)
{
	const Dimensions dimensions = Dimensions::GetInvalid();
	if (cells.size() == 0)
	{
		throw std::runtime_error("Maze must have at least 1 row");
	}
	if (cells.size() >= dimensions.rows)
	{
		throw std::runtime_error(std::format(
			"Maze has too many rows ( {} ). The maximum number of rows is ( {} )", 
			cells.size(), dimensions.rows - 1));
	}
	if (cells[0].size() == 0)
	{
		throw std::runtime_error("Maze must have at least 1 column");
	}
	if (cells[0].size() >= dimensions.cols)
	{
		throw std::runtime_error(std::format(
			"Maze has too many columns ( {} ). The maximum number of columns is ( {} )",
			cells[0].size(), dimensions.cols - 1));
	}

	for (size_t row = 0; row < cells.size(); ++row)
	{
		for (size_t col = 0; col < cells[row].size(); ++col)
		{
			if (cells[row][col] == CellType::GhostSpawn)
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
			else if (cells[row][col] == CellType::PacmanSpawn)
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

		if (cells[row].size() < cells[0].size())
		{
			Logger::cout.Warning(std::format(
				"Row with index ( {} ) has too few cells ( {} ). The expected number of columns is ( {} ). The row will be left padded with CellType::Wall cells.",
				row, cells[row].size(), cells[0].size()));

			cells[row].resize(cells[0].size(), CellType::Wall);
		}
		else if (cells[row].size() < cells[0].size())
		{
			throw std::runtime_error(std::format(
				"Row with index ( {} ) has too many cells ( {} ). The expected number of columns is ( {} ).",
				row, cells[row].size(), cells[0].size()));
		}
	}

	mCells = std::move(cells);
}

pac::CellType pac::Maze::GetCellType(Position pos) const
{
	return mCells[pos.row][pos.col];
}

bool pac::Maze::IsWalkable(Position pos) const
{
	Dimensions dimensions = GetDimensions();
	return pos.row < dimensions.rows
		&& pos.col < dimensions.cols
		&& mCells[pos.row][pos.col] != CellType::Wall;
}

bool pac::Maze::IsValid() const
{
	if (mCells.size() == 0)
	{
		return false;
	}
	if (!mGhostSpawn.IsValid() || !mPacmanSpawn.IsValid())
	{
		return false;
	}
	if (!IsWalkable(Add(mPacmanSpawn, Direction::Up()))
		&& !IsWalkable(Add(mPacmanSpawn, Direction::Down()))
		&& !IsWalkable(Add(mPacmanSpawn, Direction::Left()))
		&& !IsWalkable(Add(mPacmanSpawn, Direction::Right())))
	{
		return false;
	}

	return true;
}

void pac::Maze::EatCell(Position pos, uint64_t& score)
{
	if (mCells[pos.row][pos.col] != CellType::Coin
		&& mCells[pos.row][pos.col] != CellType::PowerUp)
	{
		throw std::runtime_error(std::format("Cell at ( {}, {} ) is not a coin or power-up", pos.row, pos.col));
	}

	if (mCells[pos.row][pos.col] == CellType::Coin)
		GetCoin(pos, score);
	else if (mCells[pos.row][pos.col] == CellType::PowerUp)
		GetPowerUp(pos, score);

	mCells[pos.row][pos.col] = CellType::Empty;
}

void pac::Maze::GetCoin(pac::Position pacmanCurrentPosition, uint64_t& score)
{
	score += 100;
}

void pac::Maze::GetPowerUp(pac::Position pacmanCurrentPosition, uint64_t& score)
{
	score += 500;
	
	// TO DO

}

void pac::Maze::EnterIntoGhost(Position pos, Pacman pacman, SFMLWindow& window)
{
	if (mCells[pos.row][pos.col] != CellType::GhostSpawn)
	{
		throw std::runtime_error(std::format("Cell at ( {}, {} ) is not a ghost spawn", pos.row, pos.col));
	}

	if (!pacman.IsPowerUpActive())
	{
		window.Close();
	}
	else
	{

	}
}

pac::Position pac::Maze::GetGhostSpawnPosition() const
{
	if (!mGhostSpawn.IsValid())
	{
		throw std::runtime_error("Ghost spawn is invalid. You must call InitCells() or ReadFromFile() before using the maze");
	}

	return mGhostSpawn;
}

pac::Position pac::Maze::GetPacmanSpawnPosition() const
{
	if (!mPacmanSpawn.IsValid())
	{
		throw std::runtime_error("Pacman spawn is invalid. You must call InitCells() or ReadFromFile() before using the maze");
	}

	return mPacmanSpawn;
}

pac::Dimensions pac::Maze::GetDimensions() const
{
	if (mCells.size() == 0)
	{
		return Dimensions::GetInvalid();
	}

	return {
		static_cast<decltype(Dimensions::rows)>(mCells.size()),
		static_cast<decltype(Dimensions::cols)>(mCells[0].size())
	};
}

bool pac::Maze::SeeEachOther(Position p1, Position p2) const
{
	return true;
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

void pac::Maze::Draw(IWindow* window) const
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
			case CellType::Empty:
			case CellType::PacmanSpawn:
			case CellType::GhostSpawn:
				break;
			default:
				throw std::runtime_error(std::format("Invalid cell type ( {} )", (size_t)GetCellType(position)));
				break;
			}
		}
	}
}
