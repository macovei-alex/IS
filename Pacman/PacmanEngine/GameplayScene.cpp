#include "GameplayScene.h"

#include "Logger/Logger.h"

#include <format>


pac::GameplayScene::GameplayScene(IWindow* window, Maze&& maze, const GameplaySettings& settings)
	: mWindow(window)
	, mMaze(std::move(maze))
	, mSettings(settings)
	, mPacman(std::make_shared<Pacman>(mMaze.GetPacmanSpawnPosition(), settings.mPacmanTicksPerMove, settings.mPowerUpDuration))
	, mScore(0)
	, mCollectibleEntities(0)
{
	for (decltype(settings.mGhostCount) i = 0; i < settings.mGhostCount; ++i)
	{
		mGhosts.push_back(Ghost(
			mMaze.GetGhostSpawnPosition(),
			settings.mGhostInitialSpawnDelay * (i + 1),
			settings));
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
				mCollectibleEntities++;
			}
			else if (mMaze.GetCellType(pos) == CellType::PowerUp)
			{
				mCollectibleEntities++;
			}
		}
	}

	Logger::cout.Debug(std::format("The maximum collectable entities for this maze is ( {} )", mCollectibleEntities));
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

pac::SceneState pac::GameplayScene::NextTick()
{
	SceneState eventsResult = HandleEvents();
	if (eventsResult != SceneState::Playing)
	{
		return eventsResult;
	}

	auto temp = mPacman->TryMove(mMaze);

	if (temp == CellType::PowerUp)
	{
		for (auto& ghost : mGhosts)
		{
			if (ghost.GetState() != Ghost::State::Dead)
			{
				ghost.SetState(Ghost::State::Scared);
			}
		}

		mScore += mSettings.mScorePerPowerUp;
		--mCollectibleEntities;
	}
	else if (temp == CellType::Coin)
	{
		mScore += mSettings.mScorePerCoin;
		--mCollectibleEntities;
	}

	for (auto& ghost : mGhosts)
	{
		SceneState collisionResult = HandleCollision(ghost);
		if (collisionResult != SceneState::Playing)
		{
			return collisionResult;
		}

		HandleStateTransition(ghost);

		ghost.NextTick(mMaze, *mPacman);
	}

	return IsGameWon() ? SceneState::Won : SceneState::Playing;
}

pac::SceneState pac::GameplayScene::HandleEvents()
{
	auto events = mWindow->GetEvents();
	if (mWindow->ShouldClose())
	{
		return SceneState::WindowClosed;
	}

	for (const auto& event : events)
	{
		Notify(event.get());
	}
	return SceneState::Playing;
}

pac::SceneState pac::GameplayScene::HandleCollision(Ghost& ghost)
{
	CollisionType collision = PacmanCollisionWith(ghost);
	if (collision == CollisionType::NoPowerUp)
	{
		return SceneState::Lost;
	}
	if (collision == CollisionType::PoweredUp)
	{
		ghost.SetState(Ghost::State::Dead);
		mScore += mSettings.mScorePerGhost;
	}

	return SceneState::Playing;
}

void pac::GameplayScene::HandleStateTransition(Ghost& ghost)
{
	Ghost::State state = ghost.GetState();
	if (state == Ghost::State::Dead)
	{
		return;
	}

	if (state == Ghost::State::Roaming)
	{
		if (mPacman->IsPoweredUp())
		{
			ghost.SetState(Ghost::State::Scared);
		}
		else if (SeesPacman(ghost))
		{
			ghost.SetState(Ghost::State::Hunting);
		}
	}
	else if (state == Ghost::State::Hunting)
	{
		if (mPacman->IsPoweredUp())
		{
			ghost.SetState(Ghost::State::Scared);
		}
		else if (!SeesPacman(ghost))
		{
			ghost.SetState(Ghost::State::Roaming);
		}
	}
	else if (state == Ghost::State::Scared)
	{
		if (mPacman->IsPoweredUp())
		{
			return;
		}
		else if (SeesPacman(ghost))
		{
			ghost.SetState(Ghost::State::Hunting);
		}
		else
		{
			ghost.SetState(Ghost::State::Roaming);
		}
	}
}

pac::CollisionType pac::GameplayScene::PacmanCollisionWith(const Ghost& ghost) const
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

bool pac::GameplayScene::SeesPacman(const Ghost& ghost) const
{
	return mMaze.SeeEachOther(mPacman->GetPosition(), ghost.GetPosition());
}

bool pac::GameplayScene::IsGameWon() const
{
	if (mCollectibleEntities != 0)
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
				count, EventTypeToStr(event)));
		}
	}
}

void pac::GameplayScene::AddListener(std::weak_ptr<IListener> listener, EventType eventType)
{
	mListeners[eventType].push_back(listener);
}

void pac::GameplayScene::RemoveListener(const IListener* listener, EventType eventType)
{
	auto& listeners = mListeners[eventType];
	auto foundIterator = std::find_if(listeners.begin(), listeners.end(),
		[listener](const std::weak_ptr<IListener>& listenerElement)
		{
			return listenerElement.lock().get() == listener;
		});

	if (foundIterator == listeners.end())
	{
		Logger::cout.Info(std::format("Listener for event type ( {} ) could not be found", EventTypeToStr(eventType)));
	}

	listeners.erase(foundIterator);
	Logger::cout.Debug(std::format("An event listener for event type ( {} ) has successfuly been removed", EventTypeToStr(eventType)));
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
