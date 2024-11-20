#include <iostream>
#include <gtest/gtest.h>
#include "PacmanEngine/Pacman.h"
#include "PacmanEngine/Maze.h"
#include "PacmanEngine/KeyPressedEvent.h"
#include "PacmanEngine/GameplaySettings.h"

TEST(PacmanTest, VerifyObjectInit)
{
	pac::GameplaySettings gps;
	pac::Pacman pacman({ 10, 10 }, gps.mPacmanTicksPerMove);
	EXPECT_EQ(pacman.GetCurrentPosition().row, 10);
	EXPECT_EQ(pacman.GetCurrentPosition().col, 10);
	EXPECT_EQ(pacman.GetTicksPerMove(), gps.mPacmanTicksPerMove);
}

TEST(PacmanTest, VerifyObjectValidPositionInit)
{
	pac::GameplaySettings gps;
	pac::Pacman pacman({ 10, 10 }, gps.mPacmanTicksPerMove);
	EXPECT_EQ(pacman.GetCurrentPosition().IsValid(), true);
}

TEST(PacmanTest, VerifyObjectInvalidPositionInit)
{
	pac::GameplaySettings gps;
	pac::Pacman pacman(pac::Position::GetInvalid(), gps.mPacmanTicksPerMove);
	EXPECT_EQ(pacman.GetCurrentPosition().IsValid(), false);
}

TEST(PacmanTest, VerifyMovementToValidAdjacentPosition)
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

	pac::KeyPressedEvent keyEvent(pac::KeyCode::Right);

	pac::Position expectedPosition = { 1, 2 };

	pacman.OnEvent(&keyEvent);
	for (int i = 0; i <= gps.mPacmanTicksPerMove; ++i)
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
		{pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall}
	};

	pac::Maze maze;
	maze.InitCells(std::move(cells));

	pac::GameplaySettings gps;
	pac::Pacman pacman({ 1, 1 }, gps.mPacmanTicksPerMove);

	pac::KeyPressedEvent keyEvent(pac::KeyCode::Right);

	pac::Position expectedPosition = pacman.GetCurrentPosition();

	pacman.OnEvent(&keyEvent);
	for (int i = 0; i <= gps.mPacmanTicksPerMove; ++i)
	{
		pacman.TryMove(maze);
	}

	EXPECT_EQ(pacman.GetCurrentPosition().row, expectedPosition.row);
	EXPECT_EQ(pacman.GetCurrentPosition().col, expectedPosition.col);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
