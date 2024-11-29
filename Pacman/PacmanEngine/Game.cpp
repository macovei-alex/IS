#include "Game.h"

#include "GameplayScene.h"
#include "Logger/Logger.h"
#include "WindowCloseEvent.h"

#include <thread>


pac::Game::Game(std::unique_ptr<IWindow> window, Maze&& maze, GameplaySettings settings, uint32_t randomSeed)
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
	Logger::cout.Info(std::format("Game with seed ( {} ) started", randomSeed));
}

void pac::Game::AddScene(std::unique_ptr<pac::IScene> scene)
{
	mScenes.push_back(std::move(scene));
}

void pac::Game::Run()
{
	static const std::chrono::milliseconds sleepDuration(1000 / mSettings.mTicksPerSecond);

	Logger::cout.Info("Game started");

	while (true)
	{
		SceneState sceneState = mScenes[mCurrentSceneIndex]->NextTick();

		if (sceneState == SceneState::Won)
		{
			Logger::cout.Info("--------  GAME WON  --------");
			mWindow->Close();
			break;
		}
		else if (sceneState == SceneState::Lost)
		{
			Logger::cout.Info("--------  GAME LOST  --------");
			mWindow->Close();
			break;
		}
		else if (sceneState == SceneState::WindowClosed)
		{
			Logger::cout.Info("Window closed");
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
