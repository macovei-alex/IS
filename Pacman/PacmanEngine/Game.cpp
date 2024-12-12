#include "Game.h"
#include "GameplayScene.h"
#include "Logger/Logger.h"
#include "LoggerInvoker.h"
#include "LogCommand.h"
#include "WindowCloseEvent.h"
#include <thread>


pac::Game::Game(std::unique_ptr<IWindow> window, Maze&& maze, const GameplaySettings& settings, uint32_t randomSeed)
	: mWindow(std::move(window))
	, mScenes()
	, mCurrentSceneIndex(0)
	, mSettings(settings)
{
	AddScene(std::make_unique<GameplayScene>(mWindow.get(), std::move(maze), settings));

	if (randomSeed == 0)
	{
		randomSeed = static_cast<uint32_t>(std::time(nullptr));
	}

	std::srand(randomSeed);

	LoggerInvoker invoker;
	std::string seedMessage = std::format("Game with seed ( {} ) started", randomSeed);
	auto logCommand = std::make_unique<pac::LogCommand>(pac::Logger::GetInstance(), seedMessage, pac::Logger::Level::Info);
	invoker.setCommand(std::move(logCommand));
	invoker.executeCommand();
}

void pac::Game::AddScene(std::unique_ptr<pac::IScene> scene)
{
	mScenes.push_back(std::move(scene));
}

void pac::Game::Run()
{
	static const std::chrono::milliseconds sleepDuration(1000 / mSettings.mTicksPerSecond);

	LoggerInvoker invoker;
	auto logCommand = std::make_unique<pac::LogCommand>(pac::Logger::GetInstance(), "Game started", pac::Logger::Level::Info);
	invoker.setCommand(std::move(logCommand));
	invoker.executeCommand();

	while (true)
	{
		SceneState sceneState = mScenes[mCurrentSceneIndex]->NextTick();

		if (sceneState == SceneState::Won)
		{
			auto logCommand = std::make_unique<pac::LogCommand>(pac::Logger::GetInstance(), "--------  GAME WON  --------", pac::Logger::Level::Info);
			invoker.setCommand(std::move(logCommand));
			invoker.executeCommand();
			mWindow->Close();
			break;
		}
		else if (sceneState == SceneState::Lost)
		{
			auto logCommand = std::make_unique<pac::LogCommand>(pac::Logger::GetInstance(), "--------  GAME LOST  --------", pac::Logger::Level::Info);
			invoker.setCommand(std::move(logCommand));
			invoker.executeCommand();
			mWindow->Close();
			break;
		}
		else if (sceneState == SceneState::WindowClosed)
		{
			auto logCommand = std::make_unique<pac::LogCommand>(pac::Logger::GetInstance(), "Window closed", pac::Logger::Level::Info);
			invoker.setCommand(std::move(logCommand));
			invoker.executeCommand();
			mWindow->Close();
			break;
		}

		mWindow->Clear();
		mScenes[mCurrentSceneIndex]->Draw();
		mWindow->Display();

		std::this_thread::sleep_for(sleepDuration);
	}
}

pac::IScene* pac::Game::GetCurrentScene() const
{
	return mScenes[mCurrentSceneIndex].get();
}
