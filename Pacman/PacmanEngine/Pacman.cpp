#include "Pacman.h"
#include "Logger/Logger.h"
#include "KeyPressedEvent.h"


pac::Pacman::Pacman(Position initialPosition, TickType ticksPerMove, TickType powerUpDuration)
	: mPosition(initialPosition)
	, mDirection()
	, mNextDirection()
	, mTick(static_cast<TickType>(-1))
	, mTicksPerMove(ticksPerMove)
	, mPowerUpDuration(powerUpDuration)
	, mLastPowerUpStart(0)
{
	// empty
}

pac::CellType pac::Pacman::TryMove(Maze& maze)
{
	++mTick;
	if (mTick % mTicksPerMove == 0)
	{
		return CellType::Empty;
	}

	if (!mPosition.IsValid())
	{
		throw std::runtime_error(std::format("Pacman current position ( {}, {} ) is invalid", mPosition.row, mPosition.col));
	}

	if (mNextDirection.IsValid())
	{
		Position newPosition = Add(mPosition, mNextDirection);
		if (newPosition.IsValid() && maze.IsWalkable(newPosition))
		{
			mDirection = mNextDirection;
			mNextDirection = Direction::GetInvalid();
		}
	}

	if (mDirection.IsValid())
	{
		Position newPosition = Add(mPosition, mDirection);
		if (!newPosition.IsValid())
		{
			return CellType::Empty;
		}

		if (maze.IsEatable(newPosition))
		{
			mPosition = newPosition;
			CellType temp = maze.EatCell(newPosition);
			if (temp == CellType::PowerUp)
			{
				SetPowerUp();
			}
			return temp;
		}
		else if (maze.IsWalkable(newPosition))
		{
			mPosition = newPosition;
		}
		else
		{
			mDirection = Direction::GetInvalid();
			mNextDirection = Direction::GetInvalid();
		}
	}

	return CellType::Empty;
}

pac::Position pac::Pacman::GetPosition() const
{
	return mPosition;
}

void pac::Pacman::SetPowerUp()
{
	mLastPowerUpStart = mTick;
}

bool pac::Pacman::IsPoweredUp() const
{
	return mLastPowerUpStart > 0
		&& mTick - mLastPowerUpStart < mPowerUpDuration;
}

void pac::Pacman::Draw(IWindow* window) const
{
	window->DrawTexture(mPosition, Textures::Pacman);
}

void pac::Pacman::OnEvent(const IEvent* event)
{
	if (event->GetType() == EventType::KeyPressed)
	{
		auto keyEvent = dynamic_cast<const KeyPressedEvent*>(event);
		if (keyEvent == nullptr)
		{
			throw std::runtime_error("Failed to cast event to KeyPressedEvent");
		}

		Direction& pos = mDirection.IsValid() ? mNextDirection : mDirection;

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