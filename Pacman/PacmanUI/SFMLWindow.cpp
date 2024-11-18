#include "SFMLWindow.h"

#include "PacmanEngine/KeyPressedEvent.h"
#include "PacmanEngine/WindowCloseEvent.h"
#include "Logger/Logger.h"

#include <format>


pac::SFMLWindow::SFMLWindow(sf::RenderWindow& renderWindow, pac::AssetManager&& assetManager)
	: mRenderWindow(renderWindow)
	, mAssetManager(std::move(assetManager))
{
	// EMPTY
}

void pac::SFMLWindow::DrawScore(const std::string& score)
{
	sf::Font font;
	if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
	{
		// error...
	}

	sf::Text text;
	text.setFont(font);
	text.setString(score);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Blue);
	text.setStyle(sf::Text::Bold);
	text.setPosition(10, 10);

	mRenderWindow.draw(text);
}

void pac::SFMLWindow::DrawTexture(pac::Position position, pac::Textures texture)
{
	int a = 50;

	sf::Sprite sprite;
	sprite = mAssetManager.GetSprite(texture);
	sprite.setPosition(position.col * a + 20.0f, position.row * a + 20.0f);
	switch (texture)
	{
	case pac::Textures::Wall:
		sprite.setScale(0.2f, 0.2f);
		break;
	case pac::Textures::Pacman:
		sprite.setScale(0.03f, 0.03f);
		break;
	case pac::Textures::Ghost:
		sprite.setScale(0.08f, 0.08f);
		break;
	case pac::Textures::Coin:
		sprite.setScale(0.02f, 0.02f);
		break;
	case pac::Textures::PowerUp:
		sprite.setScale(0.02f, 0.02f);
		break;
	default:
		break;
	}
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

std::vector<std::shared_ptr<pac::IEvent>> pac::SFMLWindow::GetEvents()
{
	std::vector<std::shared_ptr<IEvent>> events;
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

		events.push_back(convertedEvent);
	}

	return events;
}

std::shared_ptr<pac::IEvent> pac::SFMLWindow::ConvertEvent(const sf::Event& event) const
{
	static const std::unordered_map<sf::Keyboard::Key, pac::KeyCode> keyMap = {
		{sf::Keyboard::Up, pac::KeyCode::Up},
		{sf::Keyboard::Down, pac::KeyCode::Down},
		{sf::Keyboard::Left, pac::KeyCode::Left},
		{sf::Keyboard::Right, pac::KeyCode::Right}
	};

	if (event.type == sf::Event::KeyPressed)
	{
		return std::make_shared<KeyPressedEvent>(
			keyMap.find(event.key.code) != keyMap.end()
			? keyMap.at(event.key.code)
			: pac::KeyCode::Unknown);
	}

	if (event.type == sf::Event::Closed)
	{
		return std::make_shared<WindowCloseEvent>();
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