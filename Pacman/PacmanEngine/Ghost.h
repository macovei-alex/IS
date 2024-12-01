#pragma once

#include "Position.h"
#include "IPathFinder.h"
#include "Maze.h"
#include "Pacman.h"
#include "Textures.h"


namespace pac
{
	class Ghost
	{
	public:
		enum class State : uint8_t
		{
			Hunting,
			Scared,
			Roaming,
			Dead
		};

	public:
		Ghost(Position spawnPos, TickType firstSpawnDelay, const GameplaySettings& settings);
		Ghost(const Ghost& other) = delete;
		void operator=(const Ghost& other) = delete;
		Ghost(Ghost&& other) noexcept;
		void operator=(Ghost&& other) = delete;

		void NextTick(const Maze& maze, const Pacman& pacman);
		void Draw(IWindow* window) const;
		Position GetPosition() const;
		void SetState(State state);
		State GetState() const;
		TickType GetTick() const;

	private:
		Position mPosition;
		TickType mTick;
		TickType mTicksPerMove;
		TickType mTicksPerMoveScared;
		TickType mRespawnDelay;
		std::unique_ptr<IPathFinder> mPathFinder;
		State mState;

	private:
		const Position mSpawnPosition;
	};

	std::string_view StateToStr(Ghost::State state);
}
