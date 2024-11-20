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

TEST(PacmanTest, VerifyObjectInvalidTicksPerMoveInit)
{
	pac::GameplaySettings gps;
	pac::Pacman pacman({ 10, 10 }, 11);
	EXPECT_EQ(pacman.IsTicksPerMoveValid(), false);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
