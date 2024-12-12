#include "SFMLWindow.h"

#include "PacmanEngine/KeyPressedEvent.h"
#include "PacmanEngine/WindowCloseEvent.h"
#include "Logger/Logger.h"
#include "PacmanEngine/LoggerInvoker.h"
#include "PacmanEngine/LogCommand.h"

#include <memory>
#include <format>
#include <unordered_map>
#include <thread>

pac::SFMLWindow::SFMLWindow(sf::RenderWindow& renderWindow, pac::AssetManager&& assetManager)
	: mRenderWindow(renderWindow)
	, mAssetManager(std::move(assetManager))
	, mShouldClose(false)
	, mSoundPlaying(true)
{
	mSoundThread = std::make_unique<std::thread>([this]()
		{
			try
			{
				if (!mSoundBuffer.loadFromFile("assets/sounds/pacman-sound.wav"))
				{
					LoggerInvoker invoker;
					auto logCommand = std::make_unique<pac::LogCommand>(pac::Logger::GetInstance(), "Could not load the sound", pac::Logger::Level::Error);
					invoker.setCommand(std::move(logCommand));
					invoker.executeCommand();
					return;
				}
				mSound.setBuffer(mSoundBuffer);
				mSound.setVolume(10);
				mSound.play();

				while (this->mSoundPlaying)
				{
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}
			}
			catch (...)
			{
				mSoundPlaying = false;
				LoggerInvoker invoker;
				auto logCommand = std::make_unique<pac::LogCommand>(pac::Logger::GetInstance(), "Error in sound thread", pac::Logger::Level::Error);
				invoker.setCommand(std::move(logCommand));
				invoker.executeCommand();
			}
		});
}

void pac::SFMLWindow::DrawScore(ScoreType score)
{
	sf::Font font;
	if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
	{
		throw std::runtime_error("Could not load the font");
	}

	sf::Text text;
	text.setFont(font);
	text.setString(std::to_string(score));
	text.setCharacterSize(00);
	text.setFillColor(sf::Color::Blue);
	text.setStyle(sf::Text::Bold);
	text.setPosition(10, 10);

	mRenderWindow.draw(text);
}

void pac::SFMLWindow::DrawTexture(pac::Position position, pac::Textures texture)
{
	int a = 50;

	sf::Sprite sprite = mAssetManager.GetSprite(texture);
	sprite.setPosition(position.col * a + 35.0f, position.row * a + 35.0f);
	mRenderWindow.draw(sprite);
}

bool pac::SFMLWindow::IsOpen() const
{
	return mRenderWindow.isOpen();
}

bool pac::SFMLWindow::ShouldClose() const
{
	return mShouldClose;
}

void pac::SFMLWindow::Clear() const
{
	mRenderWindow.clear();
}

void pac::SFMLWindow::Display()
{
	mRenderWindow.display();
}

void pac::SFMLWindow::Close()
{
	mSoundPlaying = false;
	mSound.stop();
	mSoundThread->join();
	mRenderWindow.close();
}

std::vector<std::unique_ptr<pac::IEvent>> pac::SFMLWindow::GetEvents()
{
	std::vector<std::unique_ptr<IEvent>> events;
	sf::Event event;
	while (mRenderWindow.pollEvent(event))
	{
		auto convertedEvent = ConvertEvent(event);
		if (!convertedEvent)
		{
			continue;
		}

		if (convertedEvent->GetType() == EventType::WindowClose)
		{
			mShouldClose = true;
			continue;
		}

		events.push_back(std::move(convertedEvent));
	}

	return events;
}

std::unique_ptr<pac::IEvent> pac::SFMLWindow::ConvertEvent(const sf::Event& event) const
{
	static const std::unordered_map<sf::Keyboard::Key, pac::KeyCode> keyMap = {
		{sf::Keyboard::Up, pac::KeyCode::Up},
		{sf::Keyboard::Down, pac::KeyCode::Down},
		{sf::Keyboard::Left, pac::KeyCode::Left},
		{sf::Keyboard::Right, pac::KeyCode::Right},
		{sf::Keyboard::W, pac::KeyCode::W},
		{sf::Keyboard::A, pac::KeyCode::A},
		{sf::Keyboard::S, pac::KeyCode::S},
		{sf::Keyboard::D, pac::KeyCode::D},
	};

	if (event.type == sf::Event::KeyPressed)
	{
		return std::make_unique<KeyPressedEvent>(
			keyMap.find(event.key.code) != keyMap.end()
			? keyMap.at(event.key.code)
			: pac::KeyCode::Unknown);
	}

	if (event.type == sf::Event::Closed)
	{
		return std::make_unique<WindowCloseEvent>();
	}

	return nullptr;
}