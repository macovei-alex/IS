#pragma once
#include <gtest/gtest.h>
#include "PacmanEngine/Pacman.h"
#include "utils.h"
#include <PacmanEngine/Ghost.h>
#include <PacmanEngine/ScaredPathFinder.h>

TEST(ScaredPathFinderTest, MovesAwayFromPacmanInOpenMaze)
{
    std::string_view mazeStr = R"(
        1 1 1 1 1
        1 0 0 0 1
        1 0 0 0 1
        1 0 0 0 1
        1 1 1 1 1
    )";

    pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);
    pac::GameplaySettings settings;
    pac::Pacman pacman({ 1, 1 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration);
    pac::Ghost ghost({ 2, 2 }, 0, settings);
    pac::ScaredPathFinder pathFinder(&ghost);
    pac::Position nextMove = pathFinder.NextMove(maze, pacman);

    // {2, 3} or {3, 2} 
    bool isValidMove = (nextMove.row == 2 && nextMove.col == 3) || (nextMove.row == 3 && nextMove.col == 2);

    EXPECT_TRUE(isValidMove);
}
TEST(ScaredPathFinderTest, AvoidsWalls)
{
    std::string_view mazeStr = R"(
        1 1 1 1 1
        1 0 0 0 1
        1 0 1 0 1
        1 0 0 0 1
        1 1 1 1 1
    )";

    pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);
    pac::GameplaySettings settings;
    pac::Pacman pacman({ 1, 1 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration);
    pac::Ghost ghost({ 2, 2 }, 0, settings);

    pac::ScaredPathFinder pathFinder(&ghost);

    pac::Position nextMove = pathFinder.NextMove(maze, pacman);

    // Verify that the ghost avoids the wall and moves to {3, 2}
    EXPECT_TRUE(nextMove.row == 3 && nextMove.col == 2);
}





