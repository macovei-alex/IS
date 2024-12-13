#pragma once

#include "PacmanEngine/Textures.h"
#include <SFML/Graphics.hpp>
#include <string_view>
#include <vector>

namespace pac
{
	/**
  * @class AssetManager
  * @brief Manages the loading and retrieval of game assets such as textures and sprites.
  */
	class AssetManager
	{
	public:
		/**
   * @brief Constructs an AssetManager object.
   * @param folderPath The path to the folder containing the assets.
   * @param scaleOnLoad Whether to scale the textures on load.
   */
		AssetManager(std::string_view folderPath, bool scaleOnLoad = true);

		/**
   * @brief Retrieves the sprite associated with a given texture.
   * @param texture The texture identifier.
   * @return Reference to the sprite associated with the texture.
   */
		sf::Sprite& GetSprite(Textures texture);

	private:
		std::vector<sf::Sprite> mSprites; ///< Vector of sprites.
		std::vector<sf::Texture> mTextures; ///< Vector of textures.
	};
}