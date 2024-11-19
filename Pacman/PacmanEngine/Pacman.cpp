#include "Pacman.h"
#include "Logger/Logger.h"
#include "KeyPressedEvent.h"

pac::Pacman::Pacman(Position initialPosition, decltype(GameplaySettings::mPacmanTicksPerMove) ticksPerMove)
	: mCurrentPosition(initialPosition)
	, mCurrentDirection()
	, mNextDirection()
	, mTicksSinceLastMove(0)
	, mTicksPerMove(ticksPerMove)
{
	// empty
}

void pac::Pacman::TryMove(const Maze& maze)
{
	/*if (maze.GetCellType(mCurrentPosition) == CellType::Wall)
	{
		mCurrentDirection = mNextDirection;
		mNextDirection = Direction::GetInvalid();
		return;
	}*/

	if (mTicksSinceLastMove < mTicksPerMove)
	{
		mTicksSinceLastMove++;
		return;
	}

	mTicksSinceLastMove = 0;

	if (mCurrentPosition.IsValid() && mCurrentDirection.IsValid())
	{
		uint16_t newRow = mCurrentPosition.row + mCurrentDirection.row;
		uint16_t newCol = mCurrentPosition.col + mCurrentDirection.col;
		Position newPosition = { newRow, newCol };

		if (newPosition.IsValid())
		{
			if (maze.GetCellType(newPosition) != CellType::Wall)
			{
				mCurrentPosition = newPosition;
				
			}
			else
			{
				mCurrentDirection = mNextDirection;
				mNextDirection = Direction::GetInvalid();
			}
		}
	}

	mTicksPerMove++;
}

pac::Position pac::Pacman::GetCurrentPosition() const
{
	return mCurrentPosition;
}

decltype(pac::GameplaySettings::mPacmanTicksPerMove) pac::Pacman::GetTicksPerMove() const
{
	return mTicksPerMove;
}

void pac::Pacman::Draw(IWindow* window) const
{
	window->DrawTexture(mCurrentPosition, Textures::Pacman);
}

void pac::Pacman::OnEvent(IEvent* event)
{
	if (event->GetType() == EventType::KeyPressed)
	{
		auto keyEvent = dynamic_cast<KeyPressedEvent*>(event);

		auto& direction = mCurrentDirection.IsValid() ? mNextDirection : mCurrentDirection;

		switch (keyEvent->GetKeyCode())
		{
		case KeyCode::Up:
			direction = { -1, 0 };
			break;
		case KeyCode::Down:
			direction = { 1, 0 };
			break;
		case KeyCode::Left:
			direction = { 0, -1 };
			break;
		case KeyCode::Right:
			direction = { 0, 1 };
			break;
		case KeyCode::Unknown:
			Logger::cout.Warning("Unknown key pressed");
			break;
		default:
			Logger::cout.Warning("Unhandled key pressed");
			break;
		}
	}
}