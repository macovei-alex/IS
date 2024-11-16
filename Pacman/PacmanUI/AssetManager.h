#pragma once
#include "pch.h"

namespace pac
{
	class AssetManager
	{
	public:
		AssetManager(std::string_view folderPath);
		sf::Sprite GetPacmanSprite() const;
		sf::Sprite GetGhostSprite() const;
		sf::Sprite GetWallSprite() const;
		sf::Sprite GetCoinSprite() const;
		sf::Sprite GetPowerUpSprite() const;

	private:
		sf::Texture mPacmanTexture;
		sf::Sprite mPacmanSprite;

		sf::Texture mGhostTexture;
		sf::Sprite mGhostSprite;

		sf::Texture mWallTexture;
		sf::Sprite mWallSprite;
		
		sf::Texture mCoinTexture;
		sf::Sprite mCoinSprite;

		sf::Texture mPowerUpTexture;
		sf::Sprite mPowerUpSprite;
	};
}