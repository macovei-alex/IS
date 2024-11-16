#include "pch.h"
#include "AssetManager.h"

pac::AssetManager::AssetManager(std::string_view folderPath)
{
	mPacmanTexture.loadFromFile(std::string(folderPath) + "\\pacman.png");
	mPacmanSprite.setTexture(mPacmanTexture);

	mGhostTexture.loadFromFile(std::string(folderPath) + "\\ghost.png");
	mGhostSprite.setTexture(mGhostTexture);

	mWallTexture.loadFromFile(std::string(folderPath) + "\\wall.png");
	mWallSprite.setTexture(mWallTexture);

	mCoinTexture.loadFromFile(std::string(folderPath) + "\\coin.png");
	mCoinSprite.setTexture(mCoinTexture);

	mPowerUpTexture.loadFromFile(std::string(folderPath) + "\\powerup.png");
	mPowerUpSprite.setTexture(mPowerUpTexture);
}

sf::Sprite pac::AssetManager::GetPacmanSprite() const
{
	return mPacmanSprite;
}

sf::Sprite pac::AssetManager::GetGhostSprite() const
{
	return mGhostSprite;
}

sf::Sprite pac::AssetManager::GetWallSprite() const
{
	return mWallSprite;
}

sf::Sprite pac::AssetManager::GetCoinSprite() const
{
	return mCoinSprite;
}

sf::Sprite pac::AssetManager::GetPowerUpSprite() const
{
	return mPowerUpSprite;
}
