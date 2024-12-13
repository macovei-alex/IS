#pragma once

#include "AssetManager.h"
#include "PacmanEngine/Maze.h"
#include "PacmanEngine/IWindow.h"
#include "PacmanEngine/IEvent.h"
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <thread>

namespace pac
{
	/**
  * @class SFMLWindow
  * @brief Implementation of the IWindow interface using SFML for rendering.
  */
	class SFMLWindow : public IWindow
	{
	public:
		/**
   * @brief Constructs an SFMLWindow object.
   * @param renderWindow Reference to the SFML render window.
   * @param assetManager Asset manager for loading and managing game assets.
   */
		SFMLWindow(sf::RenderWindow& renderWindow, pac::AssetManager&& assetManager);

		/**
   * @brief Draws the score on the window.
   * @param score The current score to be displayed.
   */
		void DrawScore(ScoreType score) override;

		/**
   * @brief Draws a texture at a specified position.
   * @param position The position to draw the texture.
   * @param texture The texture to be drawn.
   */
		void DrawTexture(pac::Position position, pac::Textures texture) override;

		/**
   * @brief Checks if the window is open.
   * @return True if the window is open, false otherwise.
   */
		bool IsOpen() const override;

		/**
   * @brief Checks if the window should close.
   * @return True if the window should close, false otherwise.
   */
		bool ShouldClose() const override;

		/**
   * @brief Clears the window.
   */
		void Clear() const override;

		/**
   * @brief Displays the contents of the window.
   */
		void Display() override;

		/**
   * @brief Closes the window.
   */
		void Close() override;

		/**
   * @brief Retrieves the events from the window.
   * @return Vector of unique pointers to events.
   */
		std::vector<std::unique_ptr<pac::IEvent>> GetEvents() override;

	private:
		/**
   * @brief Converts an SFML event to a pac::IEvent.
   * @param event The SFML event to be converted.
   * @return Unique pointer to the converted event.
   */
		std::unique_ptr<pac::IEvent> ConvertEvent(const sf::Event& event) const;

	private:
		sf::RenderWindow& mRenderWindow; ///< Reference to the SFML render window.
		pac::AssetManager mAssetManager; ///< Asset manager for game assets.
		bool mShouldClose; ///< Flag indicating if the window should close.

	private:
		sf::SoundBuffer mSoundBuffer; ///< Sound buffer for playing sounds.
		sf::Sound mSound; ///< Sound object for playing sounds.
		std::unique_ptr<std::thread> mSoundThread; ///< Thread for handling sound playback.
		std::atomic<bool> mSoundPlaying; ///< Atomic flag indicating if sound is playing.
	};
}
