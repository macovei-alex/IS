#include "GameplayScene.h"

#include "Logger/Logger.h"

#include <format>


pac::GameplayScene::GameplayScene(std::shared_ptr<IWindow> window, Maze&& maze, const GameplaySettings& settings)
	: mWindow(window)
	, mMaze(std::move(maze))
	, mSettings(settings)
	, mPacman(std::make_shared<Pacman>(settings.mPacmanTicksPerMove))
{
	AddListener(mPacman, EventType::KeyPressed);
}

void pac::GameplayScene::AddListener(std::shared_ptr<IListener> listener, EventType eventType)
{
	mListeners[eventType].push_back(listener);
}

void pac::GameplayScene::RemoveListener(std::shared_ptr<IListener> listener, EventType eventType)
{
	auto& listeners = mListeners[eventType];
	auto foundIterator = std::find_if(listeners.begin(), listeners.end(),
		[&listener](const std::weak_ptr<IListener>& listenerElement)
		{
			return listenerElement.lock().get() == listener.get();
		});

	if (foundIterator == listeners.end())
	{
		Logger::cout.Info(std::format("Listener for event type ( {} ) could not be found", GetEventTypeName(eventType)));
	}

	listeners.erase(foundIterator);
	Logger::cout.Debug(std::format("An event listener for event type ( {} ) has successfuly been removed", GetEventTypeName(eventType)));
}

void pac::GameplayScene::Notify(std::shared_ptr<IEvent> event)
{
	auto foundIterator = mListeners.find(event->GetType());
	if (foundIterator == mListeners.end())
	{
		return;
	}

	std::vector<std::weak_ptr<IListener>>& listeners = foundIterator->second;
	auto from = std::remove_if(listeners.begin(), listeners.end(),
		[](const std::weak_ptr<IListener> listener) -> bool
		{
			return listener.expired();
		});

	if (from != listeners.end())
	{
		listeners.erase(from, listeners.end());

		auto count = listeners.end() - from;
		Logger::cout.Debug(std::format("( {} ) listeners were removed for events of type ( {} )",
			count, GetEventTypeName(event->GetType())));
	}

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
	// TODO: finish this
	mWindow->DrawTexture();
}

void pac::GameplayScene::NextTick()
{

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
