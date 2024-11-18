#include "pch.h"
#include "SFMLWindow.h"

pac::SFMLWindow::SFMLWindow(sf::RenderWindow& window, const AssetManager& assetManager)
	: mWindow(window)
	, mAssetManager(assetManager)
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

	mWindow.draw(text);
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
    mWindow.draw(sprite);
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