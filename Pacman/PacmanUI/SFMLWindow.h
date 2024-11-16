#pragma once
#include "pch.h"
#include <PacmanEngine/Maze.h>
#include "AssetManager.h"
#include <PacmanEngine/IWindow.h>

namespace pac
{
	class SFMLWindow : public IWindow
	{
	public:
		SFMLWindow(sf::RenderWindow& window, const Maze& maze, const AssetManager& assetManager);
		void DrawLine() override;
		void DrawText(uint16_t score) override;
		void DrawTexture() override;
		//void Draw();
	private:
		//TODO: Get pointer to IWindow that will give all the details about the position, ...
		sf::RenderWindow& mWindow;
		const Maze& mMaze;
		const AssetManager& mAssetManager;
	};
}
