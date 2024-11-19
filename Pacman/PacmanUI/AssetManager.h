#pragma once

#include "PacmanEngine/Textures.h"

#include <SFML/Graphics.hpp>
#include <string_view>
#include <vector>


namespace pac
{
	class AssetManager
	{
	public:
		AssetManager(std::string_view folderPath, bool scaleOnLoad = true);
		sf::Sprite& GetSprite(pac::Textures texture);

	private:
		std::vector<sf::Sprite> mSprites;
		std::vector<sf::Texture> mTextures;
	};
}