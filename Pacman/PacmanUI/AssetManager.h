#pragma once
#include "pch.h"
#include <PacmanEngine/Textures.h>

namespace pac
{
	class AssetManager
	{
	public:
		AssetManager(std::string_view folderPath);
		sf::Sprite GetSprite(pac::Textures texture) const;

	private:
		std::unordered_map<pac::Textures, sf::Sprite> mSprites;
		std::unordered_map<pac::Textures, sf::Texture> mTextures;
	};
}