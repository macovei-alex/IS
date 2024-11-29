#include "AssetManager.h"

#include <string>


pac::AssetManager::AssetManager(std::string_view folderPath, bool scaleOnLoad)
	: mTextures(static_cast<size_t>(Textures::_Count))
	, mSprites(static_cast<size_t>(Textures::_Count))
{
	const std::string folderStr(folderPath);

	mTextures[(size_t)Textures::Wall].loadFromFile(folderStr + "\\wall.png");
	mSprites[(size_t)Textures::Wall].setTexture(mTextures[(size_t)Textures::Wall]);

	mTextures[(size_t)Textures::Pacman].loadFromFile(folderStr + "\\pacman.png");
	mSprites[(size_t)Textures::Pacman].setTexture(mTextures[(size_t)Textures::Pacman]);

	mTextures[(size_t)Textures::Ghost].loadFromFile(folderStr + "\\ghost.png");
	mSprites[(size_t)Textures::Ghost].setTexture(mTextures[(size_t)Textures::Ghost]);

	mTextures[(size_t)Textures::ScaredGhost].loadFromFile(folderStr + "\\scared-ghost.png");
	mSprites[(size_t)Textures::ScaredGhost].setTexture(mTextures[(size_t)Textures::ScaredGhost]);


	mTextures[(size_t)Textures::Coin].loadFromFile(folderStr + "\\coin.png");
	mSprites[(size_t)Textures::Coin].setTexture(mTextures[(size_t)Textures::Coin]);

	mTextures[(size_t)Textures::PowerUp].loadFromFile(folderStr + "\\powerup.png");
	mSprites[(size_t)Textures::PowerUp].setTexture(mTextures[(size_t)Textures::PowerUp]);

	if (scaleOnLoad)
	{
		mSprites[(size_t)Textures::Wall].scale(0.2f, 0.2f);
		mSprites[(size_t)Textures::Pacman].scale(0.03f, 0.03f);
		mSprites[(size_t)Textures::Ghost].scale(0.08f, 0.08f);
		mSprites[(size_t)Textures::ScaredGhost].scale(0.15f, 0.15f);
		mSprites[(size_t)Textures::Coin].scale(0.02f, 0.02f);
		mSprites[(size_t)Textures::PowerUp].scale(0.02f, 0.02f);
	}
}

sf::Sprite& pac::AssetManager::GetSprite(Textures texture)
{
	return mSprites.at((size_t)texture);
}
