#include "AssetManager.h"

#include <string>


pac::AssetManager::AssetManager(std::string_view folderPath)
{
	const std::string folderStr(folderPath);

	mTextures[pac::Textures::Pacman].loadFromFile(folderStr + "\\pacman.png");
	mSprites[pac::Textures::Pacman].setTexture(mTextures[pac::Textures::Pacman]);

	mTextures[pac::Textures::Ghost].loadFromFile(folderStr + "\\ghost.png");
	mSprites[pac::Textures::Ghost].setTexture(mTextures[pac::Textures::Ghost]);

	mTextures[pac::Textures::Wall].loadFromFile(folderStr + "\\wall.png");
	mSprites[pac::Textures::Wall].setTexture(mTextures[pac::Textures::Wall]);

	mTextures[pac::Textures::Coin].loadFromFile(folderStr + "\\coin.png");
	mSprites[pac::Textures::Coin].setTexture(mTextures[pac::Textures::Coin]);

	mTextures[pac::Textures::PowerUp].loadFromFile(folderStr + "\\coin.png");
	mSprites[pac::Textures::PowerUp].setTexture(mTextures[pac::Textures::PowerUp]);
}

sf::Sprite pac::AssetManager::GetSprite(pac::Textures texture) const
{
	return mSprites.at(texture);
}
