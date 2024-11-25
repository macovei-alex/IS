#include "GameplayScene.h"

#include "Logger/Logger.h"

#include <format>


pac::GameplayScene::GameplayScene(IWindow* window, Maze&& maze, const GameplaySettings& settings)
	: mWindow(window)
	, mMaze(std::move(maze))
	, mSettings(settings)
	, mPacman(std::make_shared<Pacman>(mMaze.GetPacmanSpawnPosition(), settings.mPacmanTicksPerMove, settings.mPowerUpDuration))
	, mGhosts()
	, mScore(0)
	, mMaximumScore(0)
{

	for (decltype(settings.ghostCount) i = 0; i < settings.ghostCount; ++i)
	{
		mGhosts.push_back(Ghost(
			mMaze.GetGhostSpawnPosition(),
			settings.mGhostInitialSpawnDelay * (i + 1),
			settings.mGhostRespawnDelay));
		mGhosts.back().SetState(Ghost::State::Roaming);
	}

	AddListener(mPacman, EventType::KeyPressed);

	auto [height, width] = mMaze.GetDimensions();
	Position pos;

	for (pos.row = 0; pos.row < height; ++pos.row)
	{
		for (pos.col = 0; pos.col < width; ++pos.col)
		{
			if (mMaze.GetCellType(pos) == CellType::Coin)
			{
				mMaximumScore += settings.mScorePerCoin;
			}
			else if (mMaze.GetCellType(pos) == CellType::PowerUp)
			{
				mMaximumScore += settings.mScorePerPowerUp;
			}
		}
	}

	Logger::cout.Debug(std::format("The maximum score for this maze is ( {} )", mMaximumScore));
}

void pac::GameplayScene::AddListener(std::weak_ptr<IListener> listener, EventType eventType)
{
	mListeners[eventType].push_back(listener);
}

void pac::GameplayScene::RemoveListener(std::weak_ptr<IListener> listener, EventType eventType)
{
	auto listenerLocked = listener.lock();
	auto& listeners = mListeners[eventType];
	auto foundIterator = std::find_if(listeners.begin(), listeners.end(),
		[&listenerLocked](const std::weak_ptr<IListener>& listenerElement)
		{
			return listenerElement.lock().get() == listenerLocked.get();
		});

	if (foundIterator == listeners.end())
	{
		Logger::cout.Info(std::format("Listener for event type ( {} ) could not be found", GetEventTypeName(eventType)));
	}

	listeners.erase(foundIterator);
	Logger::cout.Debug(std::format("An event listener for event type ( {} ) has successfuly been removed", GetEventTypeName(eventType)));
}

void pac::GameplayScene::Notify(IEvent* event) const
{
	auto foundIterator = mListeners.find(event->GetType());
	if (foundIterator == mListeners.end())
	{
		return;
	}

	const auto& listeners = foundIterator->second;
	for (const auto& listener : listeners)
	{
		auto locked = listener.lock();
		if (!locked)
		{
			Logger::cout.Warning("Listener could not be locked for notification. Expired listeners are supposed to be removed before Notify() is called. Listener skipped, expecting removal before the next iteration");
			continue;
		}

		locked->OnEvent(event);
	}
}

void pac::GameplayScene::Draw() const
{
	mMaze.Draw(mWindow);
	mPacman->Draw(mWindow);
	for (const auto& ghost : mGhosts)
	{
		ghost.Draw(mWindow);
	}
}

void pac::GameplayScene::NextTick()
{
	auto events = mWindow->GetEvents();
	if (mWindow->ShouldClose())
	{
		return;
	}

	for (const auto& event : events)
	{
		Notify(event.get());
	}

	if (mPacman->TryMove(mMaze) == CellType::PowerUp)
	{
		for (auto& ghost : mGhosts)
		{
			ghost.SetState(Ghost::State::Scared);
		}

		mScore += mSettings.mScorePerPowerUp;
	}
	else if (mPacman->TryMove(mMaze) == CellType::Coin)
	{
		mScore += mSettings.mScorePerCoin;
	}

	for (auto& ghost : mGhosts)
	{
		if (mMaze.SeeEachOther(ghost.GetPosition(), mPacman->GetPosition()))
		{
			if (mPacman->IsPoweredUp())
			{
				ghost.SetState(Ghost::State::Scared);
			}
			else
			{
				ghost.SetState(Ghost::State::Hunting);
			}
		}
		else if (ghost.GetState() != Ghost::State::Scared)
		{
			ghost.SetState(Ghost::State::Roaming);
		}
		//daca se intalnesc pacman si ghost
		if (PacmanCollidesWith(ghost) == CollisionType::NoPowerUp)
		{
			//Final
		}
		else if (PacmanCollidesWith(ghost) == CollisionType::PoweredUp)
		{
			ghost.SetState(Ghost::State::Dead);
		}

		ghost.NextTick(mMaze, *mPacman);

	}
}

pac::CollisionType pac::GameplayScene::PacmanCollidesWith(Ghost& ghost) const
{
	if (mPacman->GetPosition() == ghost.GetPosition())
	{
		if (!mPacman->IsPoweredUp())
		{
			Logger::cout.Info("Pacman collided with a ghost. Game Over!");
			return CollisionType::NoPowerUp;
		}
		else
		{
			Logger::cout.Info("Pacman collided with a ghost. Ghost was eaten!");
			return CollisionType::PoweredUp;
		}
	}

	return CollisionType::NoCollision;
}

bool pac::GameplayScene::IsGameOver()
{
	for (int i = 0; i < mGhosts.size(); i++)
	{
		if (PacmanCollidesWith(mGhosts[i]) != CollisionType::NoPowerUp)
		{
			return false;
		}
	}

	return true;
}

void pac::GameplayScene::WinGame()
{
	if (mScore == mMaximumScore)
	{
		mWindow->Close();
		Logger::cout.Info("Game won!");
	}
}

void pac::GameplayScene::RemoveExpiredListeners()
{
	for (auto& [event, listeners] : mListeners)
	{
		auto removeFrom = std::remove_if(listeners.begin(), listeners.end(),
			[](const std::weak_ptr<IListener> listener) -> bool
			{
				return listener.expired();
			});

		if (removeFrom != listeners.end())
		{
			listeners.erase(removeFrom, listeners.end());

			auto count = listeners.end() - removeFrom;
			Logger::cout.Debug(std::format("( {} ) listeners were removed for events of type ( {} )",
				count, GetEventTypeName(event)));
		}
	}
}
