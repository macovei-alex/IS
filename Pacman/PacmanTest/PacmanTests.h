#pragma once

#include <iostream>
#include <gtest/gtest.h>
#include "PacmanEngine/Pacman.h"
#include "PacmanEngine/Maze.h"
#include "PacmanEngine/KeyPressedEvent.h"
#include "PacmanEngine/GameplaySettings.h"

#include "utils.h"


TEST(PacmanTest, VerifyPacmanInitialization)
{
	pac::GameplaySettings gps;
	pac::Pacman pacman({ 10, 10 }, gps.mPacmanTicksPerMove, gps.mPowerUpDuration);
	EXPECT_EQ(pacman.GetCurrentPosition().row, 10);
	EXPECT_EQ(pacman.GetCurrentPosition().col, 10);
}

TEST(PacmanTest, VerifyObjectValidPosition)
{
	pac::GameplaySettings gps;
	pac::Pacman pacman({ 10, 10 }, gps.mPacmanTicksPerMove, gps.mPowerUpDuration);
	EXPECT_EQ(pacman.GetCurrentPosition().IsValid(), true);
}

TEST(PacmanTest, VerifyObjectInvalidPosition)
{
	pac::GameplaySettings gps;
	pac::Pacman pacman(pac::Position::GetInvalid(), gps.mPacmanTicksPerMove, gps.mPowerUpDuration);
	EXPECT_EQ(pacman.GetCurrentPosition().IsValid(), false);
}

TEST(PacmanTest, VerifyMovementInMaze)
{
	std::string_view mazeStr = R"(
		1 1 1 1 1
		1 0 0 0 1
		1 1 1 1 1
	)";

	pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);

	pac::GameplaySettings gps;
	pac::Pacman pacman({ 1, 1 }, gps.mPacmanTicksPerMove, gps.mPowerUpDuration);

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
	std::string_view mazeStr = R"(
		1 1 1 1 1
		1 0 1 0 1
		1 0 0 0 1
		1 1 1 1 1
	)";

	pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);

	pac::GameplaySettings gps;
	pac::Pacman pacman({ 1, 1 }, gps.mPacmanTicksPerMove, gps.mPowerUpDuration);

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