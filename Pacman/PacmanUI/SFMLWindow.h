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
		SFMLWindow(sf::RenderWindow& window, const AssetManager& assetManager);
		void DrawScore(const std::string& score) override;
		void DrawTexture(pac::Position position, pac::Textures texture) override;
	private:
		//TODO: Get pointer to IWindow that will give all the details about the position, ...
		sf::RenderWindow& mWindow;
		const AssetManager& mAssetManager;
	};
}
