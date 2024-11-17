#include "GameplayScene.h"

#include "Logger/Logger.h"
#include <format>


pac::GameplayScene::GameplayScene(std::shared_ptr<IWindow> window, Maze&& maze, const GameplaySettings& settings)
	: mWindow(window)
	, mMaze(std::move(maze))
	, mSettings(settings)
{
	// empty
}

void pac::GameplayScene::AddListener(std::shared_ptr<IListener> listener, EventType eventType)
{
	mListeners[eventType].push_back(listener);
}

void pac::GameplayScene::RemoveListener(std::shared_ptr<IListener> listener, EventType eventType)
{
	auto& vec = mListeners[eventType];
	auto foundIterator = std::find(vec.begin(), vec.end(), listener);

	if (foundIterator == vec.end())
	{
		Logger::cout.Info(std::format("Listener for event type ( {} ) could not be found", GetEventTypeName(eventType)));
	}

	vec.erase(foundIterator);
	Logger::cout.Debug(std::format("An event listener for event type ( {} ) has successfuly been removed", GetEventTypeName(eventType)));
}

void pac::GameplayScene::Notify(std::shared_ptr<IEvent> newEvent)
{
	auto foundIterator = mListeners.find(newEvent->GetType());
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
			count, GetEventTypeName(newEvent->GetType())));
	}

	for (const auto& listener : listeners)
	{
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
