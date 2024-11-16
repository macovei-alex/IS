#include "pch.h"
#include "SFMLWindow.h"

pac::SFMLWindow::SFMLWindow(sf::RenderWindow& window, const Maze& maze, const AssetManager& assetManager)
	: mWindow(window)
	, mMaze(maze)
	, mAssetManager(assetManager)
{
	// EMPTY
}

void pac::SFMLWindow::DrawLine()
{
    auto [height, width] = mMaze.GetSize();

    int a = 50;

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            if (mMaze.GetCellType(Position(i, j)) == CellType::Wall)
            {
                sf::Sprite sprite;
                sprite = mAssetManager.GetWallSprite();
                sprite.setPosition(j * a + 20, i * a + 20);
                sprite.setScale(0.2f, 0.2f);
                mWindow.draw(sprite);
            }
        }
    }
}

void pac::SFMLWindow::DrawText(uint16_t score)
{
	sf::Font font;
	if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
	{
		// error...
	}

	sf::Text text;
	text.setFont(font);
	text.setString(std::to_string(score));
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Blue);
	text.setStyle(sf::Text::Bold);
	text.setPosition(10, 10);

	mWindow.draw(text);
}

void pac::SFMLWindow::DrawTexture()
{
    auto [height, width] = mMaze.GetSize();

    int a = 55;

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            sf::Sprite sprite;
            switch (mMaze.GetCellType(Position(i, j))) {
            case CellType::PacmanSpawn:
                sprite = mAssetManager.GetPacmanSprite();
                sprite.setPosition(j * a + 20, i * a+20);
                sprite.setScale(0.03f, 0.03f);
                break;
            case CellType::GhostSpawn:
                sprite = mAssetManager.GetGhostSprite();
                sprite.setPosition(j * a + 20, i * a + 20);
                sprite.setScale(0.08f, 0.08f);
                break;
            case CellType::Coin:
                sprite = mAssetManager.GetCoinSprite();
                sprite.setPosition(j * a + 20, i * a + 20);
                sprite.setScale(0.02f, 0.02f);
                break;
            case CellType::PowerUp:
                sprite = mAssetManager.GetPowerUpSprite();
                sprite.setPosition(j * a + 20, i * a + 20);
                sprite.setScale(0.02f, 0.02f);
                break;
            }

            mWindow.draw(sprite);
        }
    }
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