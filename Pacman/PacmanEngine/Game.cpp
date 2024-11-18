#include "Game.h"

#include "Logger/Logger.h"

pac::Game::Game(std::shared_ptr<pac::IWindow> window, std::shared_ptr<pac::IScene> currentScene)
{
	mWindow = window;
	mCurrentScene = currentScene;
	mScenes.push_back(currentScene);
}

void pac::Game::AddScene(std::shared_ptr<pac::IScene> scene)
{
	mScenes.push_back(scene);
}

void pac::Game::TestFunc()
{
	Logger::cout.Info("Hello, World!");
}

void pac::Game::Run()
{
	//while (true)
	//{
	//	//mCurrentScene->NextTick();
	//	
	//}

	mCurrentScene->Draw();
}

std::shared_ptr<pac::IScene> pac::Game::GetCurrentScene() const
{
	return mCurrentScene;
}
