#pragma once

#include "pch.h"
#include "Logger/Logger.h"


namespace pac {

	// Game
	enum class EventType
	{
		KeyPressed,
		PowerUp
	};

	enum class KeyCode : uint8_t
	{
		Up,
		Down,
		Left,
		Right,
		Unknown
	};

	class IEvent
	{
		virtual EventType GetType() const = 0;
	};

	class KeyPressedEvent : public IEvent
	{
	public:
		KeyPressedEvent(KeyCode keyCode) : mKeyCode(keyCode) { }
		KeyCode GetKeyCode() const { return mKeyCode; }
		EventType GetType() const override { return EventType::KeyPressed; }

	private:
		KeyCode mKeyCode;
	};

	class PowerUpEvent : public IEvent
	{
	public:
		EventType GetType() const override { return EventType::PowerUp; }
	};

	class IWindow
	{
		virtual std::queue<std::shared_ptr<IEvent>> GetEvents() = 0;
		virtual void DrawLine() = 0;
		virtual void DrawText() = 0;
		virtual void DrawTextures(pac::Textures) = 0;
	};

	class IGame
	{
	public:
		// static IGame* MakeGame(IWindow*) { return Game(IWindow*); };
	};

	class IListener
	{
	};

	class Maze
	{
	public:
		Maze(std::string_view filePath) {}
	};

	enum class Textures : uint8_t
	{
	};

	class Game
	{
	public:
		Game(std::shared_ptr<IWindow> window) : mWindow(window) {}
		void Run() {}
	private:
		std::shared_ptr<IWindow> mWindow;
	};

	struct GameplaySettings
	{
		uint16_t ghostCount;
		uint16_t ticksPerMovePacman;
		uint16_t ticksPerMoveGhost;
		uint16_t ticksPerMoveGhostPowerup;
	};


	class SFMLWindow : public IWindow
	{
	public:
		SFMLWindow(sf::VideoMode mode, const sf::String& title, std::unordered_map<sf::Keyboard::Key, KeyCode> keyMap, pac::AssetManager&& assetManager) :
			mWindow(mode, title),
			mKeyMap(std::move(keyMap)),
			mAssetManager(std::move(assetManager))
		{
		}

		std::shared_ptr<IEvent> ConvertEvent(const sf::Event& event) const {
			switch (event.type)
			{
			case sf::Event::KeyPressed:

				switch (event.key.code)
				{
				case sf::Keyboard::Up: return std::make_shared<KeyPressedEvent>(KeyCode::Up);
				case sf::Keyboard::Down: return std::make_shared<KeyPressedEvent>(KeyCode::Down);
				case sf::Keyboard::Left: return std::make_shared<KeyPressedEvent>(KeyCode::Left);
				case sf::Keyboard::Right: return std::make_shared<KeyPressedEvent>(KeyCode::Right);
				}

				return std::make_shared<KeyPressedEvent>(KeyCode::Unknown);
			}
		}

		std::queue<std::shared_ptr<IEvent>> GetEvents() override {
			std::queue<std::shared_ptr<IEvent>> events;
			sf::Event event;
			while (mWindow.pollEvent(event)) {
				events.push(ConvertEvent(event));
			}
			return events;
		}

	private:
		sf::RenderWindow mWindow;
		std::unordered_map<sf::Keyboard::Key, KeyCode> mKeyMap;
		pac::AssetManager mAssetManager;
	};

	class AssetManager
	{
	public:
		AssetManager(std::string_view folderPath) {}

		virtual Maze* LoadMaze(std::string_view filePath) {}

	private:
		std::vector<std::shared_ptr<pac::Textures>> textures;
	};

	class TestWindow : public IWindow
	{
	public:
		std::shared_ptr<IEvent> ConvertEvent(const sf::Event& event) const {}
		std::queue<std::shared_ptr<IEvent>> GetEvents() override {
			std::queue<std::shared_ptr<IEvent>> events;
			events.push(std::make_shared<KeyPressedEvent>(KeyCode::Up));
			return events;
		}
	};
}

int main()
{
	// Flow made by Andrei:

	pac::AssetManager assetManager = pac::AssetManager("assets");
	std::shared_ptr<pac::IWindow> window = std::make_shared< pac::SFMLWindow>(sf::VideoMode(800, 600), sf::String("Pacman"), std::unordered_map<sf::Keyboard::Key, pac::KeyCode>(), assetManager);
	pac::Game game = pac::Game(window);
	game.Run();

	pac::Logger::cout.Debug("Hello, World!");
	sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "My window");

	size_t lastUpdate = 0;
	renderWindow.setFramerateLimit(60);
	while (renderWindow.isOpen()) {
		sf::Event event;
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				renderWindow.close();
			}
		}

		renderWindow.clear(sf::Color::Black);
		renderWindow.display();
	}

	pac::GameplaySettings settings;
	settings.ghostCount = 3;
	settings.ticksPerMovePacman = 2;
	settings.ticksPerMoveGhost = 2;
	settings.ticksPerMoveGhostPowerup = 3;

	std::unordered_map<pac::EventType, std::vector<pac::IListener*>> listeners;
}