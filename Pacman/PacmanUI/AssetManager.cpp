#include "AssetManager.h"

#include <string>


pac::AssetManager::AssetManager(std::string_view folderPath, bool scaleOnLoad)
	: mTextures(static_cast<size_t>(pac::Textures::_Count))
	, mSprites(static_cast<size_t>(pac::Textures::_Count))
{
	const std::string folderStr(folderPath);

	mTextures[(size_t)pac::Textures::Wall].loadFromFile(folderStr + "\\wall.png");
	mSprites[(size_t)pac::Textures::Wall].setTexture(mTextures[(size_t)pac::Textures::Wall]);

	mTextures[(size_t)pac::Textures::Pacman].loadFromFile(folderStr + "\\pacman.png");
	mSprites[(size_t)pac::Textures::Pacman].setTexture(mTextures[(size_t)pac::Textures::Pacman]);

	mTextures[(size_t)pac::Textures::Ghost].loadFromFile(folderStr + "\\ghost.png");
	mSprites[(size_t)pac::Textures::Ghost].setTexture(mTextures[(size_t)pac::Textures::Ghost]);

	mTextures[(size_t)pac::Textures::Coin].loadFromFile(folderStr + "\\coin.png");
	mSprites[(size_t)pac::Textures::Coin].setTexture(mTextures[(size_t)pac::Textures::Coin]);

	mTextures[(size_t)pac::Textures::PowerUp].loadFromFile(folderStr + "\\powerup.png");
	mSprites[(size_t)pac::Textures::PowerUp].setTexture(mTextures[(size_t)pac::Textures::PowerUp]);

	if (scaleOnLoad)
	{
		mSprites[(size_t)pac::Textures::Wall].scale(0.2f, 0.2f);
		mSprites[(size_t)pac::Textures::Pacman].scale(0.03f, 0.03f);
		mSprites[(size_t)pac::Textures::Ghost].scale(0.08f, 0.08f);
		mSprites[(size_t)pac::Textures::Coin].scale(0.02f, 0.02f);
		mSprites[(size_t)pac::Textures::PowerUp].scale(0.02f, 0.02f);
	}
}

sf::Sprite& pac::AssetManager::GetSprite(pac::Textures texture)
{
	return mSprites.at((size_t)texture);
}
