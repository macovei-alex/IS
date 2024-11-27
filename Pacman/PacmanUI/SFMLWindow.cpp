#include "SFMLWindow.h"

#include "PacmanEngine/KeyPressedEvent.h"
#include "PacmanEngine/WindowCloseEvent.h"
#include "Logger/Logger.h"

#include <memory>
#include <format>
#include <unordered_map>


pac::SFMLWindow::SFMLWindow(sf::RenderWindow& renderWindow, pac::AssetManager&& assetManager)
	: mRenderWindow(renderWindow)
	, mAssetManager(std::move(assetManager))
{
	// EMPTY
}

void pac::SFMLWindow::DrawScore(int64_t score)
{
	sf::Font font;
	if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
	{
		throw std::runtime_error("Could not load the font");
	}

	sf::Text text;
	text.setFont(font);
	text.setString(std::to_string(score));
	text.setCharacterSize(20);
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

		if (convertedEvent->GetType() == EventType::WindowClosed)
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

//void pac::SFMLWindow::Draw()
//{
//    auto [height, width] = mMaze.GetSize();
//
//    int a = 130;
//
//    for (size_t i = 0; i < height; ++i) {
//        for (size_t j = 0; j < width; ++j) {
//            sf::Sprite sprite;
//            switch (mMaze.GetCellType(Position(i, j))) {
//            case CellType::PacmanSpawn:
//                sprite = mAssetManager.GetPacmanSprite();
//                sprite.setPosition(j * a, i * a);
//                sprite.setScale(0.1f, 0.1f);
//                break;
//            case CellType::GhostSpawn:
//                sprite = mAssetManager.GetGhostSprite();
//                sprite.setPosition(j * a, i * a);
//                sprite.setScale(0.2f, 0.2f);
//                break;
//            case CellType::Wall:
//                sprite = mAssetManager.GetWallSprite();
//                sprite.setPosition(j * a, i * a);
//                sprite.setScale(0.1f, 0.1f);
//                break;
//            case CellType::Coin:
//                sprite = mAssetManager.GetCoinSprite();
//                sprite.setPosition(j * a, i * a);
//                sprite.setScale(0.1f, 0.1f);
//                break;
//            case CellType::PowerUp:
//                sprite = mAssetManager.GetPowerUpSprite();
//                sprite.setPosition(j * a, i * a);
//                sprite.setScale(0.08f, 0.08f);
//                break;
//            }
//            
//            mWindow.draw(sprite);
//        }
//    }
//}