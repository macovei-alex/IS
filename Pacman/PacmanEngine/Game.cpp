#include "Game.h"

#include "GameplayScene.h"
#include "Logger/Logger.h"
#include "WindowCloseEvent.h"


pac::Game::Game(std::unique_ptr<IWindow> window, Maze&& maze, const GameplaySettings& settings)
	: mWindow(std::move(window))
	, mScenes()
{
	// empty
	AddScene(std::make_unique<GameplayScene>(mWindow.get(), std::move(maze), settings));
}

void pac::Game::AddScene(std::unique_ptr<pac::IScene> scene)
{
	mScenes.push_back(std::move(scene));
}

void pac::Game::Run()
{
	Logger::cout.Info("Game running");

	while (mWindow->IsOpen())
	{
		mScenes[mCurrentSceneIndex]->NextTick();

		if (mWindow->ShouldClose())
		{
			mWindow->Close();
			break;
		}

		mWindow->Clear();
		mScenes[mCurrentSceneIndex]->Draw();
		mWindow->Display();

	}

	Logger::cout.Debug("Game closed successfully");
}

pac::IScene* pac::Game::GetCurrentScene() const
{
	return mScenes[mCurrentSceneIndex].get();
}
