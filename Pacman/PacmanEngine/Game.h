#pragma once

#include <vector>
#include "IScene.h"
#include "IWindow.h"
#include "IGame.h"

namespace pac
{
	class Game : public IGame
	{
	public:
		Game(std::shared_ptr<pac::IWindow> window, std::shared_ptr<pac::IScene> currentScene);
		void AddScene(std::shared_ptr<pac::IScene> scene);
		void TestFunc();
		void Run() override;
		std::shared_ptr<pac::IScene> GetCurrentScene() const;
	private:
		std::vector<std::shared_ptr<pac::IScene>> mScenes;
		std::shared_ptr<pac::IScene> mCurrentScene;
		std::shared_ptr<pac::IWindow> mWindow;
	};
}
