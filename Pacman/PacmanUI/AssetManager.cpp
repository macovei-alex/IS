#include "pch.h"
#include "AssetManager.h"

pac::AssetManager::AssetManager(std::string_view folderPath)
{
	sf::Texture texture;
	texture.loadFromFile(std::string(folderPath) + "\\pacman.png");
	mTextures[pac::Textures::Pacman] = texture;
	mSprites[pac::Textures::Pacman].setTexture(mTextures[pac::Textures::Pacman]);

	texture.loadFromFile(std::string(folderPath) + "\\ghost.png");
	mTextures[pac::Textures::Ghost] = texture;
	mSprites[pac::Textures::Ghost].setTexture(mTextures[pac::Textures::Ghost]);

	texture.loadFromFile(std::string(folderPath) + "\\wall.png");
	mTextures[pac::Textures::Wall] = texture;
	mSprites[pac::Textures::Wall].setTexture(mTextures[pac::Textures::Wall]);

	texture.loadFromFile(std::string(folderPath) + "\\coin.png");
	mTextures[pac::Textures::Coin] = texture;
	mSprites[pac::Textures::Coin].setTexture(mTextures[pac::Textures::Coin]);

	texture.loadFromFile(std::string(folderPath) + "\\powerup.png");
	mTextures[pac::Textures::PowerUp] = texture;
	mSprites[pac::Textures::PowerUp].setTexture(mTextures[pac::Textures::PowerUp]);
}

sf::Sprite pac::AssetManager::GetSprite(pac::Textures texture) const
{
	return mSprites.at(texture);
}
