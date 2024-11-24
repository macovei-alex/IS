#include "Pacman.h"
#include "Logger/Logger.h"
#include "KeyPressedEvent.h"


pac::Pacman::Pacman(Position initialPosition, decltype(GameplaySettings::mPacmanTicksPerMove) pacmanTicksPerMove)
	: mCurrentPosition(initialPosition)
	, mCurrentDirection()
	, mNextDirection()
	, mTicksSinceLastMove(0)
	, mTicksPerMove(pacmanTicksPerMove)
	, mScore(0)
	, mIsPowerUpActive(false)
{
	// empty
}

void pac::Pacman::TryMove(Maze& maze)
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

	if (!mCurrentPosition.IsValid())
	{
		throw std::runtime_error(std::format("Pacman current position ( {}, {} ) is invalid", mCurrentPosition.row, mCurrentPosition.col));
	}

	if (mNextDirection.IsValid())
	{
		Position newPosition = Add(mCurrentPosition, mNextDirection);
		if (newPosition.IsValid() && maze.GetCellType(newPosition) == CellType::Empty)
		{
			mCurrentDirection = mNextDirection;
			mNextDirection = Direction::GetInvalid();
		}
	}

	if (mCurrentDirection.IsValid())
	{
		Position newPosition = Add(mCurrentPosition, mCurrentDirection);
		if (maze.GetCellType(newPosition) == CellType::Coin
			|| maze.GetCellType(newPosition) == CellType::PowerUp)
		{
			mScore += maze.EatCell(newPosition);
		}
		if (newPosition.IsValid())
		{
			if (maze.IsWalkable(newPosition))
			{
				mCurrentPosition = newPosition;
			}
			else
			{
				mCurrentDirection = Direction::GetInvalid();
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

void pac::Pacman::IncreaseScoreCoinCell()
{
	mScore += 100;
}

void pac::Pacman::IncreaseScorePowerUpCell()
{
	mScore += 500;
}

uint64_t pac::Pacman::GetScore() const
{
	return mScore;
}

void pac::Pacman::SetIsPowerUpActive(bool isPowerUpActive)
{
	mIsPowerUpActive = isPowerUpActive;
}

bool pac::Pacman::IsPowerUpActive() const
{
	return mIsPowerUpActive;
}

uint16_t pac::Pacman::GetPowerUpDuration() const
{
	return mPowerUpDuration;
}

void pac::Pacman::Draw(IWindow* window) const
{
	window->DrawTexture(mCurrentPosition, Textures::Pacman);
	window->DrawScore(mScore);
}

void pac::Pacman::OnEvent(IEvent* event)
{
	if (event->GetType() == EventType::KeyPressed)
	{
		auto keyEvent = dynamic_cast<KeyPressedEvent*>(event);
		Direction& pos = mCurrentDirection.IsValid() ? mNextDirection : mCurrentDirection;

		switch (keyEvent->GetKeyCode())
		{
		case KeyCode::Up:
		case KeyCode::W:
			pos = Direction::Up();
			break;
		case KeyCode::Down:
		case KeyCode::S:
			pos = Direction::Down();
			break;
		case KeyCode::Left:
		case KeyCode::A:
			pos = Direction::Left();
			break;
		case KeyCode::Right:
		case KeyCode::D:
			pos = Direction::Right();
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