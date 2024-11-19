#pragma once

#include "PacmanEngine/Textures.h"

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string_view>


namespace pac
{
	class AssetManager
	{
	public:
		AssetManager(std::string_view folderPath, bool scaleOnLoad = true);
		sf::Sprite GetSprite(pac::Textures texture) const;

	private:
		std::unordered_map<pac::Textures, sf::Sprite> mSprites;
		std::unordered_map<pac::Textures, sf::Texture> mTextures;
	};
}