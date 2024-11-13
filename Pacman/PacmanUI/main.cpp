#include "pch.h"
#include "Logger/Logger.h"
#include "main.h"
// #include "PacmanEngine/Game.h"

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

	class Maze : public IMaze
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
		void Run();
	private:
		std::shared_ptr<IWindow> mWindow;
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

	class IMaze
	{
	};

	class AssetManager
	{
	public:
		AssetManager(std::string_view folderPath) {}

		virtual IMaze* LoadMaze(std::string_view filePath) {}

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

	/*pac::Logger::cout.Debug("Hello, World!");
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	size_t lastUpdate = 0;
	window.setFramerateLimit(10);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		window.display();
	}*/

	/*GameSettings gameSettings;
	gameSettings.ghostCount = 3;
	gameSettings.ticksPerMovePacman = 2;
	gameSettings.ticksPerMoveGhost = 2;
	gameSettings.ticksPerMoveGhostPowerup = 3;
	gameSettings.maze = Maze();

	IMaze* imaze = Maze();
	Maze* maze = dynamic_cast<Maze*>(imaze);

	std::map<EventType, std::vector<IListener*>> listeners;*/
}
