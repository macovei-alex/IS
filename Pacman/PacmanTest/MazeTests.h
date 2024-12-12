#pragma once

#include <iostream>
#include <gtest/gtest.h>
#include "PacmanEngine/Pacman.h"
#include "PacmanEngine/Maze.h"
#include "PacmanEngine/KeyPressedEvent.h"
#include "PacmanEngine/GameplaySettings.h"

#include "utils.h"

TEST(MazeTest, VerifyMazeInitialization)
{
	std::string_view mazeStr = R"(
		1 1 1 1 1 1 1
		1 0 0 3 4 5 1
		1 1 1 1 1 1 1
	)";

	pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);

	EXPECT_EQ(maze.GetDimensions().rows, 3);
	EXPECT_EQ(maze.GetDimensions().cols, 7);
}

TEST(MazeTest, VerifyGetCellType)
{
	std::string_view mazeStr = R"(
		1 1 1 1 1 1 1
		1 0 0 3 4 5 1
		1 1 1 1 1 1 1
	)";

	pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);

	EXPECT_EQ(maze.GetCellType({ 1, 0 }), pac::CellType::Wall);
	EXPECT_EQ(maze.GetCellType({ 1, 1 }), pac::CellType::Empty);
	EXPECT_EQ(maze.GetCellType({ 1, 0 }), pac::CellType::Coin);
	EXPECT_EQ(maze.GetCellType({ 1, 3 }), pac::CellType::PowerUp);
	EXPECT_EQ(maze.GetCellType({ 1, 4 }), pac::CellType::GhostSpawn);
	EXPECT_EQ(maze.GetCellType({ 1, 5 }), pac::CellType::PacmanSpawn);
}

TEST(MazeTest, VerifyIsWalkable)
{
	std::string_view mazeStr = R"(
		1 1 1 1 1 1 1
		1 0 0 3 4 5 1
		1 1 1 1 1 1 1
	)";

	pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);

	EXPECT_EQ(maze.IsWalkable({ 1, 0 }), false);
	EXPECT_EQ(maze.IsWalkable({ 1, 1 }), true);
	EXPECT_EQ(maze.IsWalkable({ 1, 0 }), true);
	EXPECT_EQ(maze.IsWalkable({ 1, 3 }), true);
	EXPECT_EQ(maze.IsWalkable({ 1, 4 }), true);
	EXPECT_EQ(maze.IsWalkable({ 1, 5 }), true);
}

TEST(MazeTest, VerifyEatCell)
{
	std::string_view mazeStr = R"(
		1 1 1 1 1 1 1
		1 0 0 3 4 5 1
		1 1 1 1 1 1 1
	)";

	pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);
	uint64_t score = 0;

	maze.EatCell({ 1, 0 });
	EXPECT_EQ(maze.GetCellType({ 1, 0 }), pac::CellType::Empty);
	maze.EatCell({ 1, 3 });
	EXPECT_EQ(maze.GetCellType({ 1, 3 }), pac::CellType::Empty);

	EXPECT_THROW(maze.EatCell({ 1, 4 }), std::runtime_error);
	EXPECT_THROW(maze.EatCell({ 1, 5 }), std::runtime_error);
}

TEST(MazeTest, VerifyGetPacmanSpawnPosition)
{
	std::string_view mazeStr = R"(
		1 1 1 1 1 1 1
		1 0 0 5 0 0 1
		1 1 1 1 1 1 1
	)";

	pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);

	EXPECT_EQ(maze.GetPacmanSpawnPosition().row, 1);
	EXPECT_EQ(maze.GetPacmanSpawnPosition().col, 3);
}

TEST(MazeTest, VerifyMazeWithoutPacmanCell)
{
	std::string_view mazeStr = R"(
		1 1 1 1 1 1 1
		1 0 0 0 0 0 1
		1 1 1 1 1 1 1
	)";

	pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);

	EXPECT_THROW(maze.GetPacmanSpawnPosition(), std::runtime_error);
	EXPECT_THROW(maze.GetGhostSpawnPosition(), std::runtime_error);
}

TEST(MazeTest, VerifyGetGhostSpawnPosition)
{
	std::string_view mazeStr = R"(
		1 1 1 1 1 1 1
		1 0 0 4 0 0 1
		1 1 1 1 1 1 1
	)";

	pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);

	EXPECT_EQ(maze.GetGhostSpawnPosition().row, 1);
	EXPECT_EQ(maze.GetGhostSpawnPosition().col, 3);
}

TEST(MazeTest, VerifyMazeWithoutGhostCell)
{
	std::string_view mazeStr = R"(
		1 1 1 1 1 1 1
		1 0 0 0 0 0 1
		1 1 1 1 1 1 1
	)";

	pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);

	EXPECT_THROW(maze.GetGhostSpawnPosition(), std::runtime_error);
}

TEST(MazeTest, VerifyGetDimensions)
{
	pac::Maze maze;

	EXPECT_THROW(maze.InitCells({}), std::runtime_error);

	std::string_view mazeStr = R"(
		1 1 1
		1 0 1
		1 1 1
	)";

	maze = pac::test::ReadMazeFromStr(mazeStr);

	pac::Dimensions expectedDimension = { 3, 3 };

	EXPECT_EQ(maze.GetDimensions().rows, expectedDimension.rows);
	EXPECT_EQ(maze.GetDimensions().cols, expectedDimension.cols);
}