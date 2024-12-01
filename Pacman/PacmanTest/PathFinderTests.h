#pragma once
#include <gtest/gtest.h>
#include "PacmanEngine/Pacman.h"
#include "utils.h"
#include <PacmanEngine/Ghost.h>
#include <PacmanEngine/ScaredPathFinder.h>
#include <PacmanEngine/HuntPathFinder.h>
#include <PacmanEngine/RoamingPathFinder.h>

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

TEST(HuntPathFinderTest, FindsShortestPathToPacmanInOpenMaze)
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
    pac::Ghost ghost({ 3, 3 }, 0, settings);
    pac::HuntPathFinder pathFinder(&ghost);

    pac::Position nextMove = pathFinder.NextMove(maze, pacman);

    bool isCorrectMove = (nextMove.row == 2 && nextMove.col == 3);
    EXPECT_TRUE(isCorrectMove);
}

TEST(RoamingPathFinderTest, ChoosesRandomValidPosition)
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
    pac::Ghost ghost({ 2, 2 }, 0, settings);
    pac::RoamingPathFinder pathFinder(&ghost);

    pac::Position nextMove = pathFinder.NextMove(maze, pac::Pacman({ 1, 1 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration));

    EXPECT_TRUE(nextMove.IsValid());
    EXPECT_FALSE(nextMove == ghost.GetPosition());
}
TEST(RoamingPathFinderTest, MovesTowardsRandomPosition)
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
    pac::Ghost ghost({ 2, 2 }, 0, settings);
    pac::RoamingPathFinder pathFinder(&ghost);

    pac::Position nextMove = pathFinder.NextMove(maze, pac::Pacman({ 1, 1 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration));

    EXPECT_TRUE(nextMove != ghost.GetPosition());

    nextMove = pathFinder.NextMove(maze, pac::Pacman({ 1, 1 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration));

    EXPECT_TRUE(nextMove != ghost.GetPosition());
}
TEST(RoamingPathFinderTest, ChangesDirectionWhenReachingEndOfPath)
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
    pac::Ghost ghost({ 1, 1 }, 0, settings); 
    pac::RoamingPathFinder pathFinder(&ghost);


    pac::Position originalPosition = ghost.GetPosition();

    pac::Position nextMove1 = pathFinder.NextMove(maze, pac::Pacman({ 3, 3 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration));
    pac::Position nextMove2 = pathFinder.NextMove(maze, pac::Pacman({ 3, 3 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration));


    EXPECT_NE(nextMove1, nextMove2); 
}


















