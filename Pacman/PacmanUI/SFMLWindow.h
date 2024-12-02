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
	class SFMLWindow : public IWindow
	{
	public:
		SFMLWindow(sf::RenderWindow& renderWindow, pac::AssetManager&& assetManager);
		void DrawScore(ScoreType score) override;
		void DrawTexture(pac::Position position, pac::Textures texture) override;
		bool IsOpen() const override;
		bool ShouldClose() const override;
		void Clear() const override;
		void Display() override;
		void Close() override;
		std::vector<std::unique_ptr<pac::IEvent>> GetEvents() override;

	private:
		std::unique_ptr<pac::IEvent> ConvertEvent(const sf::Event& event) const;

	private:
		sf::RenderWindow& mRenderWindow;
		sf::SoundBuffer buffer;
		sf::Sound sound;
		pac::AssetManager mAssetManager;
		std::unique_ptr<std::thread> mSoundThread;
		std::atomic<bool> mSoundPlaying;
		bool mShouldClose;
	};
}
