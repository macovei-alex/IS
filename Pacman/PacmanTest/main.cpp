#include <iostream>
#include <gtest/gtest.h>
#include "PacmanEngine/Pacman.h"
#include "PacmanEngine/Maze.h"
#include "PacmanEngine/KeyPressedEvent.h"
#include "PacmanEngine/GameplaySettings.h"

TEST(PacmanTest, VerifyObjectInitialization)
{
	pac::GameplaySettings gps;
	pac::Pacman pacman({ 10, 10 }, gps.mPacmanTicksPerMove);
	EXPECT_EQ(pacman.GetCurrentPosition().row, 10);
	EXPECT_EQ(pacman.GetCurrentPosition().col, 10);
	EXPECT_EQ(pacman.GetTicksPerMove(), gps.mPacmanTicksPerMove);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
