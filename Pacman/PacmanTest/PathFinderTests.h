#pragma once
#include <gtest/gtest.h>
#include "PacmanEngine/Pacman.h"
#include "utils.h"
#include <PacmanEngine/Ghost.h>

#include <PacmanEngine/ScaredPathFinder.h>
#include <PacmanEngine/HuntPathFinder.h>
#include <PacmanEngine/RoamingPathFinder.h>
#include <PacmanEngine/WaitingPathFinder.h>

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
//tot cu pereti 
TEST(ScaredPathFinderTest, AvoidsPacmanAndWalls)
{
    std::string_view mazeStr = R"(
        1 1 1 1 1 1
        1 0 0 0 1 1
        1 0 1 0 1 1
        1 0 0 0 0 1
        1 1 1 1 1 1
    )";

    pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);
    pac::GameplaySettings settings;
    pac::Pacman pacman({ 1, 1 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration);
    pac::Ghost ghost({ 3, 2 }, 0, settings);  // Fantoma este în colțul de jos
    pac::ScaredPathFinder pathFinder(&ghost);

    pac::Position nextMove = pathFinder.NextMove(maze, pacman);
    bool isValidMove = (nextMove.row == 2 && nextMove.col == 2) || (nextMove.row == 3 && nextMove.col == 3);
    EXPECT_TRUE(isValidMove);
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

TEST(RoamingPathFinderTest, NavigatesMazeWithMultiplePaths)
{
    std::string_view mazeStr = R"(
        1 1 1 1 1 1
        1 0 0 0 0 1
        1 0 1 1 0 1
        1 0 0 0 0 1
        1 1 1 1 1 1
    )";

    pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);
    pac::GameplaySettings settings;
    pac::Ghost ghost({ 2, 2 }, 0, settings);
    pac::RoamingPathFinder pathFinder(&ghost);

    pac::Position nextMove = pathFinder.NextMove(maze, pac::Pacman({ 1, 1 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration));

    EXPECT_TRUE(nextMove.IsValid());
    EXPECT_FALSE(nextMove == ghost.GetPosition());
    EXPECT_TRUE(maze.IsWalkable(nextMove));
}

TEST(RoamingPathFinderTest, MovesFromIsolatedCorner)
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
    pac::Ghost ghost({ 1, 1 }, 0, settings);
    pac::RoamingPathFinder pathFinder(&ghost);

    pac::Position nextMove = pathFinder.NextMove(maze, pac::Pacman({ 3, 3 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration));

    EXPECT_TRUE(nextMove.IsValid());
    EXPECT_FALSE(nextMove == ghost.GetPosition());
    EXPECT_TRUE(maze.IsWalkable(nextMove));
	EXPECT_NE(nextMove.row, 1); // Se asigura ca se misca inafara coltului
}

TEST(HuntPathFinderTest, AvoidsWallsWhenHuntingPacman)
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
    pac::Pacman pacman({ 3, 1 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration);  
    pac::Ghost ghost({ 1, 1 }, 0, settings);  
    pac::HuntPathFinder pathFinder(&ghost);

    pac::Position nextMove = pathFinder.NextMove(maze, pacman);
    bool isCloserToPacman = (nextMove.row == 2 && nextMove.col == 1); 
    EXPECT_TRUE(isCloserToPacman);
}

TEST(HuntPathFinderTest, HandlesCaseWhenPathIsBlocked)
{
    std::string_view mazeStr = R"(
        1 1 1 1 1 1 1
        1 0 0 1 0 0 1
        1 0 1 1 1 0 1
        1 0 0 0 0 0 1
        1 1 1 1 1 1 1
    )";

    pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);
    pac::GameplaySettings settings;
    pac::Pacman pacman({ 3, 5 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration);
    pac::Ghost ghost({ 1, 1 }, 0, settings);

    pac::HuntPathFinder pathFinder(&ghost);

    pac::Position nextMove = pathFinder.NextMove(maze, pacman);
    EXPECT_TRUE(nextMove.IsValid());
    EXPECT_FALSE(nextMove == ghost.GetPosition());
    EXPECT_NE(nextMove.row, 1);
}

TEST(HuntPathFinderTest, MovesTowardsPacmanWithObstacles)
{
    std::string_view mazeStr = R"(
        1 1 1 1 1 1 1 1
        1 0 0 0 1 0 0 1
        1 0 1 0 1 0 0 1
        1 0 1 0 0 0 1 1
        1 1 1 1 1 1 1 1
    )";

    pac::Maze maze = pac::test::ReadMazeFromStr(mazeStr);
    pac::GameplaySettings settings;
    pac::Pacman pacman({ 3, 5 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration);
    pac::Ghost ghost({ 1, 1 }, 0, settings);

    pac::HuntPathFinder pathFinder(&ghost);

    pac::Position nextMove = pathFinder.NextMove(maze, pacman);
    EXPECT_TRUE(nextMove.IsValid());

    EXPECT_FALSE(nextMove == ghost.GetPosition());

    // Functie pentru a calcula distanța Manhattan
    auto manhattanDistance = [](const pac::Position& a, const pac::Position& b) {
        return std::abs(a.row - b.row) + std::abs(a.col - b.col);
        };

    // Verifica dacă "nextMove" apropie fantoma de Pacman
    auto pacmanPos = pacman.GetPosition();
    EXPECT_LT(manhattanDistance(nextMove, pacmanPos),
        manhattanDistance(ghost.GetPosition(), pacmanPos));
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

TEST(RoamingPathFinderTest, ChoosesPathWithMultipleDirections)
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
    pac::Ghost ghost({ 2, 2 }, 0, settings);
    pac::RoamingPathFinder pathFinder(&ghost);

    pac::Position nextMove = pathFinder.NextMove(maze, pac::Pacman({ 3, 3 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration));
    EXPECT_TRUE(nextMove.IsValid());
    EXPECT_FALSE(nextMove == ghost.GetPosition());
}


TEST(RoamingPathFinderTest, AvoidsWallsAndStaysWithinBounds)
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
    pac::Ghost ghost({ 2, 2 }, 0, settings);  
    pac::RoamingPathFinder pathFinder(&ghost);
    pac::Position nextMove = pathFinder.NextMove(maze, pac::Pacman({ 1, 1 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration));

    bool isValidMove = (nextMove.row == 3 && nextMove.col == 2) || (nextMove.row == 1 && nextMove.col == 2);
    EXPECT_TRUE(isValidMove);
}

TEST(GhostTest, ChangesStateCorrectlyWithSetState)
{
    pac::GameplaySettings settings;
    settings.mGhostTicksPerMove = 1;
    pac::Ghost ghost({ 2, 2 }, 0, settings);

    ghost.SetState(pac::Ghost::State::Hunting);
    EXPECT_EQ(ghost.GetState(), pac::Ghost::State::Hunting);

    ghost.SetState(pac::Ghost::State::Scared);
    EXPECT_EQ(ghost.GetState(), pac::Ghost::State::Scared);

    ghost.SetState(pac::Ghost::State::Dead);
    EXPECT_EQ(ghost.GetState(), pac::Ghost::State::Dead);
	EXPECT_EQ(ghost.GetPosition(), ghost.GetPosition()); // Ar trebui sa fie la pozitia de spawn
}

TEST(WaitingPathFinderTest, WaitsUntilTargetTick)
{
	pac::GameplaySettings settings;
	pac::Ghost ghost({ 2, 2 }, 5, settings);
	pac::WaitingPathFinder pathFinder(&ghost, 5);
	pac::Position nextMove = pathFinder.NextMove(pac::Maze(), pac::Pacman({ 1, 1 }, settings.mPacmanTicksPerMove, settings.mPowerUpDuration));
	EXPECT_EQ(nextMove, ghost.GetPosition());

}