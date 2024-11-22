#include <iostream>
#include <gtest/gtest.h>
#include "PacmanEngine/Pacman.h"
#include "PacmanEngine/Maze.h"
#include "PacmanEngine/KeyPressedEvent.h"
#include "PacmanEngine/GameplaySettings.h"

TEST(PacmanTest, VerifyPacmanInitialization)
{
	pac::GameplaySettings gps;
	pac::Pacman pacman({ 10, 10 }, gps.mPacmanTicksPerMove);
	EXPECT_EQ(pacman.GetCurrentPosition().row, 10);
	EXPECT_EQ(pacman.GetCurrentPosition().col, 10);
	EXPECT_EQ(pacman.GetTicksPerMove(), gps.mPacmanTicksPerMove);
}

TEST(PacmanTest, VerifyObjectValidPosition)
{
	pac::GameplaySettings gps;
	pac::Pacman pacman({ 10, 10 }, gps.mPacmanTicksPerMove);
	EXPECT_EQ(pacman.GetCurrentPosition().IsValid(), true);
}

TEST(PacmanTest, VerifyObjectInvalidPosition)
{
	pac::GameplaySettings gps;
	pac::Pacman pacman(pac::Position::GetInvalid(), gps.mPacmanTicksPerMove);
	EXPECT_EQ(pacman.GetCurrentPosition().IsValid(), false);
}

TEST(PacmanTest, VerifyMovementInMaze)
{
	std::vector<std::vector<pac::CellType>> cells = {
			{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall},
			{pac::CellType::Wall, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::Wall},
			{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall}
	};

	pac::Maze maze;
	maze.InitCells(std::move(cells));

	pac::GameplaySettings gps;
	pac::Pacman pacman({ 1, 1 }, gps.mPacmanTicksPerMove);

	pac::KeyPressedEvent keyEventRight(pac::KeyCode::Right);
	pacman.OnEvent(&keyEventRight);

	pac::Position expectedPosition = { 1, 3 };

	while (pacman.GetCurrentPosition() != expectedPosition)
	{
		pacman.TryMove(maze);
	}

	EXPECT_EQ(pacman.GetCurrentPosition().row, expectedPosition.row);
	EXPECT_EQ(pacman.GetCurrentPosition().col, expectedPosition.col);

	pac::KeyPressedEvent keyEventUp(pac::KeyCode::Up);
	pacman.OnEvent(&keyEventUp);

	while (pacman.GetCurrentPosition() != expectedPosition)
	{
		pacman.TryMove(maze);
	}

	EXPECT_EQ(pacman.GetCurrentPosition().row, expectedPosition.row);
	EXPECT_EQ(pacman.GetCurrentPosition().col, expectedPosition.col);

	pac::KeyPressedEvent keyEventDown(pac::KeyCode::Down);
	pacman.OnEvent(&keyEventDown);

	while (pacman.GetCurrentPosition() != expectedPosition)
	{
		pacman.TryMove(maze);
	}

	EXPECT_EQ(pacman.GetCurrentPosition().row, expectedPosition.row);
	EXPECT_EQ(pacman.GetCurrentPosition().col, expectedPosition.col);

	pac::KeyPressedEvent keyEventLeft(pac::KeyCode::Left);
	pacman.OnEvent(&keyEventLeft);

	expectedPosition = { 1, 1 };

	while (pacman.GetCurrentPosition() != expectedPosition)
	{
		pacman.TryMove(maze);
	}

	EXPECT_EQ(pacman.GetCurrentPosition().row, expectedPosition.row);
	EXPECT_EQ(pacman.GetCurrentPosition().col, expectedPosition.col);
}

TEST(PacmanTest, VerifyMovementToWallCell)
{
	std::vector<std::vector<pac::CellType>> cells = {
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Empty, pac::CellType::Wall, pac::CellType::Empty, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall}
	};

	pac::Maze maze;
	maze.InitCells(std::move(cells));

	pac::GameplaySettings gps;
	pac::Pacman pacman({ 1, 1 }, gps.mPacmanTicksPerMove);

	pac::KeyPressedEvent keyEventRight(pac::KeyCode::Right);
	pacman.OnEvent(&keyEventRight);

	pac::Position expectedPosition = pacman.GetCurrentPosition();

	while (pacman.GetCurrentPosition() != expectedPosition)
	{
		pacman.TryMove(maze);
	}

	EXPECT_EQ(pacman.GetCurrentPosition().row, expectedPosition.row);
	EXPECT_EQ(pacman.GetCurrentPosition().col, expectedPosition.col);

	pac::KeyPressedEvent keyEventLeft(pac::KeyCode::Left);
	pacman.OnEvent(&keyEventLeft);

	while (pacman.GetCurrentPosition() != expectedPosition)
	{
		pacman.TryMove(maze);
	}

	EXPECT_EQ(pacman.GetCurrentPosition().row, expectedPosition.row);
	EXPECT_EQ(pacman.GetCurrentPosition().col, expectedPosition.col);

	pac::KeyPressedEvent keyEventDown(pac::KeyCode::Down);
	pacman.OnEvent(&keyEventDown);

	expectedPosition = { 2, 1 };

	while (pacman.GetCurrentPosition() != expectedPosition)
	{
		pacman.TryMove(maze);
	}

	EXPECT_EQ(pacman.GetCurrentPosition().row, expectedPosition.row);
	EXPECT_EQ(pacman.GetCurrentPosition().col, expectedPosition.col);

	pacman.OnEvent(&keyEventRight);

	expectedPosition = { 2, 3 };

	while (pacman.GetCurrentPosition() != expectedPosition)
	{
		pacman.TryMove(maze);
	}

	EXPECT_EQ(pacman.GetCurrentPosition().row, expectedPosition.row);
	EXPECT_EQ(pacman.GetCurrentPosition().col, expectedPosition.col);
}

TEST(MazeTest, VerifyMazeInitialization)
{
	std::vector<std::vector<pac::CellType>> cells = {
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Empty, pac::CellType::Coin, pac::CellType::PowerUp, pac::CellType::GhostSpawn, pac::CellType::PacmanSpawn, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall}
	};

	pac::Maze maze;
	maze.InitCells(std::move(cells));

	EXPECT_EQ(maze.GetDimensions().rows, 3);
	EXPECT_EQ(maze.GetDimensions().cols, 7);
}

TEST(MazeTest, VerifyGetCellType)
{
	std::vector<std::vector<pac::CellType>> cells = {
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Empty, pac::CellType::Coin, pac::CellType::PowerUp, pac::CellType::GhostSpawn, pac::CellType::PacmanSpawn, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall}
	};

	pac::Maze maze;
	maze.InitCells(std::move(cells));

	EXPECT_EQ(maze.GetCellType({ 1, 0 }), pac::CellType::Wall);
	EXPECT_EQ(maze.GetCellType({ 1, 1 }), pac::CellType::Empty);
	EXPECT_EQ(maze.GetCellType({ 1, 2 }), pac::CellType::Coin);
	EXPECT_EQ(maze.GetCellType({ 1, 3 }), pac::CellType::PowerUp);
	EXPECT_EQ(maze.GetCellType({ 1, 4 }), pac::CellType::GhostSpawn);
	EXPECT_EQ(maze.GetCellType({ 1, 5 }), pac::CellType::PacmanSpawn);
}

TEST(MazeTest, VerifyIsWalkable)
{
	std::vector<std::vector<pac::CellType>> cells = {
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Empty, pac::CellType::Coin, pac::CellType::PowerUp, pac::CellType::GhostSpawn, pac::CellType::PacmanSpawn, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall}
	};

	pac::Maze maze;
	maze.InitCells(std::move(cells));

	EXPECT_EQ(maze.IsWalkable({ 1, 0 }), false);
	EXPECT_EQ(maze.IsWalkable({ 1, 1 }), true);
	EXPECT_EQ(maze.IsWalkable({ 1, 2 }), true);
	EXPECT_EQ(maze.IsWalkable({ 1, 3 }), true);
	EXPECT_EQ(maze.IsWalkable({ 1, 4 }), true);
	EXPECT_EQ(maze.IsWalkable({ 1, 5 }), true);
}

TEST(MazeTest, VerifyEatCell)
{
	std::vector<std::vector<pac::CellType>> cells = {
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Empty, pac::CellType::Coin, pac::CellType::Coin, pac::CellType::Coin, pac::CellType::PowerUp, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall}
	};

	pac::Maze maze;
	maze.InitCells(std::move(cells));

	maze.EatCell({ 1, 2 });
	EXPECT_EQ(maze.GetCellType({ 1, 2 }), pac::CellType::Empty);
	maze.EatCell({ 1, 3 });
	EXPECT_EQ(maze.GetCellType({ 1, 3 }), pac::CellType::Empty);
	maze.EatCell({ 1, 4 });
	EXPECT_EQ(maze.GetCellType({ 1, 4 }), pac::CellType::Empty);
	maze.EatCell({ 1, 5 });
	EXPECT_EQ(maze.GetCellType({ 1, 5 }), pac::CellType::Empty);
}

TEST(MazeTest, VerifyGetPacmanSpawnPosition)
{
	std::vector<std::vector<pac::CellType>> cells = {
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::PacmanSpawn, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall}
	};

	pac::Maze maze;
	maze.InitCells(std::move(cells));

	EXPECT_EQ(maze.GetPacmanSpawnPosition().row, 1);
	EXPECT_EQ(maze.GetPacmanSpawnPosition().col, 3);
}

TEST(MazeTest, VerifyMazeWithoutPacmanCell)
{
	std::vector<std::vector<pac::CellType>> cells = {
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall}
	};

	pac::Maze maze;
	maze.InitCells(std::move(cells));

	EXPECT_THROW(maze.GetPacmanSpawnPosition(), std::runtime_error);
}

TEST(MazeTest, VerifyGetGhostSpawnPosition)
{
	std::vector<std::vector<pac::CellType>> cells = {
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::GhostSpawn, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall}
	};

	pac::Maze maze;
	maze.InitCells(std::move(cells));

	EXPECT_EQ(maze.GetGhostSpawnPosition().row, 1);
	EXPECT_EQ(maze.GetGhostSpawnPosition().col, 3);
}

TEST(MazeTest, VerifyMazeWithoutGhostCell)
{
	std::vector<std::vector<pac::CellType>> cells = {
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::Empty, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall}
	};

	pac::Maze maze;
	maze.InitCells(std::move(cells));

	EXPECT_THROW(maze.GetGhostSpawnPosition(), std::runtime_error);
}

TEST(MazeTest, VerifyGetDimensions)
{
	std::vector<std::vector<pac::CellType>> cells;

	pac::Maze maze;

	EXPECT_THROW(maze.InitCells(std::move(cells)), std::runtime_error);

	cells = {
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Empty, pac::CellType::Wall},
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall}
	};

	maze.InitCells(std::move(cells));

	pac::Dimensions expectedDimension = maze.GetDimensions();

	EXPECT_EQ(maze.GetDimensions().rows, expectedDimension.rows);
	EXPECT_EQ(maze.GetDimensions().cols, expectedDimension.cols);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
