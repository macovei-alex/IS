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
	, mCollecatbleEntities(0)
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

	Dimensions dimensions = mMaze.GetDimensions();
	Position pos;

	for (pos.row = 0; pos.row < dimensions.rows; ++pos.row)
	{
		for (pos.col = 0; pos.col < dimensions.cols; ++pos.col)
		{
			if (mMaze.GetCellType(pos) == CellType::Coin)
			{
				mCollecatbleEntities++;
			}
			else if (mMaze.GetCellType(pos) == CellType::PowerUp)
			{
				mCollecatbleEntities++;
			}
		}
	}

	Logger::cout.Debug(std::format("The maximum collectable entities for this maze is ( {} )", mCollecatbleEntities));
}

void pac::GameplayScene::Draw() const
{
	mMaze.Draw(mWindow);
	mPacman->Draw(mWindow);
	for (const auto& ghost : mGhosts)
	{
		ghost.Draw(mWindow);
	}
	mWindow->DrawScore(mScore);
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

	auto temp = mPacman->TryMove(mMaze);

	if (temp == CellType::PowerUp)
	{
		for (auto& ghost : mGhosts)
		{
			ghost.SetState(Ghost::State::Scared);
		}

		mScore += mSettings.mScorePerPowerUp;
		mCollecatbleEntities--;
	}
	else if (temp == CellType::Coin)
	{
		mScore += mSettings.mScorePerCoin;
		mCollecatbleEntities--;
	}

	for (auto& ghost : mGhosts)
	{
		if (mMaze.SeeEachOther(ghost.GetPosition(), mPacman->GetPosition()))
		{
			if (!mPacman->IsPoweredUp())
			{
				ghost.SetState(Ghost::State::Hunting);
			}
		}
		else if (ghost.GetState() != Ghost::State::Scared)
		{
			ghost.SetState(Ghost::State::Roaming);
		}

		//daca se intalnesc pacman si ghost
		CollisionType collision = PacmanCollidesWith(ghost);
		//thsi should be called when we verify LoseGame
		/*if (collision == CollisionType::NoPowerUp)
		{
			mWindow->Close();
		}*/
		if (collision == CollisionType::PoweredUp)
		{
			ghost.SetState(Ghost::State::Dead);
			mScore += mSettings.mScorePerGhost;
		}

		ghost.NextTick(mMaze, *mPacman);

	}
}

pac::CollisionType pac::GameplayScene::PacmanCollidesWith(const Ghost& ghost) const
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
	for (size_t i = 0; i < mGhosts.size(); i++)
	{
		if (PacmanCollidesWith(mGhosts[i]) != CollisionType::NoPowerUp)
		{
			return false;
		}
	}

	return true;
}

bool pac::GameplayScene::IsWinGame()
{
	if (mCollecatbleEntities != 0)
	{
		return false;
	}

	return true;
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
