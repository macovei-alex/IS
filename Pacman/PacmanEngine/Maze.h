#pragma once

#include "IWindow.h"
#include "Dimensions.h"
#include "GameplaySettings.h"
#include <memory>
#include <vector>
#include <string_view>

namespace pac
{
	/**
  * @enum CellType
  * @brief Represents the type of a cell in the maze.
  */
	enum class CellType : uint8_t
	{
		Empty,
		Wall,
		Coin,
		PowerUp,
		GhostSpawn,
		PacmanSpawn
	};

	/**
  * @class Maze
  * @brief Represents the maze in the game.
  */
	class Maze
	{
	public:
		/**
   * @brief Constructs a Maze object.
   */
		Maze();

		/**
   * @brief Initializes the cells of the maze.
   * @param cells A 2D vector of cell types.
   */
		void InitCells(std::vector<std::vector<CellType>>&& cells);

		/**
   * @brief Gets the type of a cell at a given position.
   * @param pos The position of the cell.
   * @return The type of the cell.
   */
		CellType GetCellType(Position pos) const;

		/**
   * @brief Checks if a cell at a given position is eatable.
   * @param pos The position of the cell.
   * @return True if the cell is eatable, false otherwise.
   */
		bool IsEatable(Position pos) const;

		/**
   * @brief Checks if a cell at a given position is walkable.
   * @param pos The position of the cell.
   * @return True if the cell is walkable, false otherwise.
   */
		bool IsWalkable(Position pos) const;

		/**
   * @brief Checks if the maze is valid.
   * @return True if the maze is valid, false otherwise.
   */
		bool IsValid() const;

		/**
   * @brief Eats a cell at a given position.
   * @param pos The position of the cell.
   * @return The type of the cell that was eaten.
   */
		pac::CellType EatCell(Position pos);

		/**
   * @brief Gets the spawn position for ghosts.
   * @return The spawn position for ghosts.
   */
		Position GetGhostSpawnPosition() const;

		/**
   * @brief Gets the spawn position for Pacman.
   * @return The spawn position for Pacman.
   */
		Position GetPacmanSpawnPosition() const;

		/**
   * @brief Gets the dimensions of the maze.
   * @return The dimensions of the maze.
   */
		Dimensions GetDimensions() const;

		/**
   * @brief Checks if two positions can see each other.
   * @param p1 The first position.
   * @param p2 The second position.
   * @return True if the positions can see each other, false otherwise.
   */
		bool SeeEachOther(Position p1, Position p2) const;

		/**
   * @brief Reads the maze from a file.
   * @param filename The name of the file.
   */
		void ReadMazeFromFile(std::string_view filename);

		/**
   * @brief Draws the maze.
   * @param window Pointer to the game window.
   */
		void Draw(IWindow* window) const;

		/**
   * @brief Gets a random walkable position in the maze.
   * @return A random walkable position.
   */
		Position GetRandomWalkablePosition() const;

		/**
   * @brief Calculates the shortest path between two positions.
   * @param start The start position.
   * @param end The end position.
   * @return A vector of positions representing the shortest path.
   */
		std::vector<Position> CalculateShortestPath(Position start, Position end) const;

	private:
		std::vector<std::vector<CellType>> mCells; ///< 2D vector of cell types.
		std::vector<Position> mWalkablePositions; ///< Vector of walkable positions.
		mutable std::vector<Position> mParentVec; ///< Vector of parent positions for pathfinding.
		mutable std::vector<bool> mVisitedVec; ///< Vector of visited positions for pathfinding.
		Position mGhostSpawn; ///< Spawn position for ghosts.
		Position mPacmanSpawn; ///< Spawn position for Pacman.
	};
}