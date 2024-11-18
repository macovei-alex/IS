#include "Pacman.h"
#include "Logger/Logger.h"
#include "KeyPressedEvent.h"

pac::Pacman::Pacman(uint16_t ticksPerMove) : mCurrentPosition(), mCurrentDirection(Direction::Right), mNextDirection(Direction::Right), mTicksSinceLastMove(0), mTicksPerMove(ticksPerMove)
{
}

void pac::Pacman::TryMove(const Maze& maze)
{
	if (maze.GetCellType(mCurrentPosition) == CellType::Wall)
	{
		mCurrentDirection = mNextDirection;
		mNextDirection = Direction::Unknown;
		return;
	}

	if (mTicksSinceLastMove == mTicksPerMove)
	{
		mTicksSinceLastMove++;
		return;
	}
	
	mTicksSinceLastMove = 1;
	Position moveDirection;

	switch (mCurrentDirection)
	{
	case Direction::Up:
		moveDirection.row = -1;
		break;
	case Direction::Down:
		moveDirection.row = 1;
		break;
	case Direction::Left:
		moveDirection.col = -1;
		break;
	case Direction::Right:
		moveDirection.col = 1;
		break;
	case Direction::Unknown:
		Logger::cout.Debug("Pacman stopped");
		break;
	}
}

pac::Position pac::Pacman::GetCurrentPosition()
{
	return mCurrentPosition;
}

void pac::Pacman::OnEvent(std::shared_ptr<IEvent> event)
{
	if (event->GetType() == EventType::KeyPressed)
	{
		auto keyEvent = std::dynamic_pointer_cast<KeyPressedEvent>(event);

		switch (keyEvent->GetKeyCode())
		{
		case KeyCode::Up:
			mNextDirection = Direction::Up;
			break;
		case KeyCode::Down:
			mNextDirection = Direction::Down;
			break;
		case KeyCode::Left:
			mNextDirection = Direction::Left;
			break;
		case KeyCode::Right:
			mNextDirection = Direction::Right;
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