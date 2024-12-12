﻿#include "Maze.h"

#include "LoggerInvoker.h"
#include "LogCommand.h"
#include "Logger/Logger.h"
#include "Direction.h"
#include "Pacman.h"

#include <format>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

#define POS(pos) (pos.row * colCount + pos.col)


pac::Maze::Maze()
	: mGhostSpawn(pac::Position::GetInvalid())
	, mPacmanSpawn(pac::Position::GetInvalid())
	, mWalkablePositions()
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

	mWalkablePositions.reserve(cells.size() * cells[0].size());

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
					static_cast<PosType>(row),
					static_cast<PosType>(col)
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
					static_cast<PosType>(row),
					static_cast<PosType>(col)
				};
			}

			if (cells[row][col] != CellType::Wall)
			{
				mWalkablePositions.push_back({
					static_cast<PosType>(row),
					static_cast<PosType>(col)
					});
			}
		}

		if (cells[row].size() < cells[0].size())
		{
			std::string logMessage = std::format(
				"Row with index ( {} ) has too few cells ( {} ). The expected number of columns is ( {} ). The row will be left padded with CellType::Wall cells.",
				row, cells[row].size(), cells[0].size());
			LoggerInvoker invoker;
			auto logCommand = std::make_unique<pac::LogCommand>(pac::Logger::GetInstance(), logMessage, pac::Logger::Level::Warning);
			invoker.setCommand(std::move(logCommand));
			invoker.executeCommand();
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

bool pac::Maze::IsEatable(Position pos) const
{
	return mCells[pos.row][pos.col] == CellType::Coin
		|| mCells[pos.row][pos.col] == CellType::PowerUp;
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

pac::CellType pac::Maze::EatCell(Position pos)
{
	if (mCells[pos.row][pos.col] != CellType::Coin
		&& mCells[pos.row][pos.col] != CellType::PowerUp)
	{
		throw std::runtime_error(std::format("Cell at ( {}, {} ) is not a coin or power-up", pos.row, pos.col));
	}

	CellType temp = mCells[pos.row][pos.col];

	mCells[pos.row][pos.col] = CellType::Empty;
	return temp;
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
		static_cast<PosType>(mCells.size()),
		static_cast<PosType>(mCells[0].size())
	};
}

bool pac::Maze::SeeEachOther(Position p1, Position p2) const
{
	return p1.NumberOfCellsTo(p2) < 4;
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

pac::Position pac::Maze::GetRandomWalkablePosition() const
{
	if (mWalkablePositions.size() == 0)
	{
		throw std::runtime_error("There are no walkable positions in the maze");
	}

	return mWalkablePositions[std::rand() % mWalkablePositions.size()];
}

std::vector<pac::Position> pac::Maze::CalculateShortestPath(Position start, Position end) const
{
	const Dimensions dimensions = GetDimensions();
	const size_t size = (size_t)dimensions.rows * dimensions.cols;

	std::vector<Position> path;
	path.reserve(size);

	if (mParentVec.size() < size)
	{
		mParentVec.resize(size, Position::GetInvalid());
		mVisitedVec.resize(size, false);
	}

	for (size_t i = 0; i < size; i++)
	{
		mVisitedVec[i] = false;
		mParentVec[i] = Position::GetInvalid();
	}

	const auto colCount = dimensions.cols;

	std::queue<Position> bfsQueue;

	bfsQueue.push(start);
	mVisitedVec[POS(start)] = true;

	while (!bfsQueue.empty())
	{
		Position current = bfsQueue.front();
		bfsQueue.pop();

		if (current == end)
		{
			Position nextMove = mParentVec[POS(current)];
			path.push_back(current);
			while (nextMove != start && nextMove.IsValid())
			{
				current = nextMove;
				nextMove = mParentVec[POS(nextMove)];
				path.push_back(current);
			}
			break;
		}

		for (Direction direction : Direction::AllDirections())
		{
			Position neighbor = Add(current, direction);

			if (!mVisitedVec[POS(neighbor)] && GetCellType(neighbor) != CellType::Wall)
			{
				bfsQueue.push(neighbor);
				mVisitedVec[POS(neighbor)] = true;
				mParentVec[POS(neighbor)] = current;
			}
		}
	}

	return path;
}
