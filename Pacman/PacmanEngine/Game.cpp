#include "Game.h"

#include "GameplayScene.h"
#include "Logger/Logger.h"
#include "WindowCloseEvent.h"


pac::Game::Game(std::shared_ptr<IWindow> window, Maze&& maze, const GameplaySettings& settings)
	: mWindow(window)
	, mScenes({ std::make_shared<GameplayScene>(window, std::move(maze), settings) })
{
	// empty
}

void pac::Game::AddScene(std::shared_ptr<pac::IScene> scene)
{
	mScenes.push_back(scene);
}

void pac::Game::Run()
{
	while (mWindow->IsOpen())
	{
		auto events = mWindow->GetEvents();

		if (mWindow->ShouldClose())
		{
			mWindow->Close();
			break;
		}

		mScenes[mCurrentSceneIndex]->NextTick();

		mWindow->Clear();
		mScenes[mCurrentSceneIndex]->Draw();
		mWindow->Display();
	}

	Logger::cout.Debug("Game closed successfully");
}

std::shared_ptr<pac::IScene> pac::Game::GetCurrentScene() const
{
	return mScenes[mCurrentSceneIndex];
}

void pac::Game::OnEvent(std::shared_ptr<IEvent> event)
{
	if (event->GetType() == EventType::WindowClosed)
	{
		auto keyEvent = std::static_pointer_cast<WindowCloseEvent>(event);
		mWindow->Close();
	}
}
