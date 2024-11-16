#include "pch.h"
#include "SFMLWindow.h"

pac::SFMLWindow::SFMLWindow(sf::RenderWindow& window, const Maze& maze, const AssetManager& assetManager)
	: mWindow(window)
	, mMaze(maze)
	, mAssetManager(assetManager)
{
	// EMPTY
}

void pac::SFMLWindow::Draw()
{
    auto [height, width] = mMaze.GetSize();

    int a = 130;

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            sf::Sprite sprite;
            switch (mMaze.GetCellType(Position(i, j))) {
            case CellType::PacmanSpawn:
                sprite = mAssetManager.GetPacmanSprite();
                sprite.setPosition(j * a, i * a);
                sprite.setScale(0.1f, 0.1f);
                break;
            case CellType::GhostSpawn:
                sprite = mAssetManager.GetGhostSprite();
                sprite.setPosition(j * a, i * a);
                sprite.setScale(0.2f, 0.2f);
                break;
            case CellType::Wall:
                sprite = mAssetManager.GetWallSprite();
                sprite.setPosition(j * a, i * a);
                sprite.setScale(0.1f, 0.1f);
                break;
            case CellType::Coin:
                sprite = mAssetManager.GetCoinSprite();
                sprite.setPosition(j * a, i * a);
                sprite.setScale(0.1f, 0.1f);
                break;
            case CellType::PowerUp:
                sprite = mAssetManager.GetPowerUpSprite();
                sprite.setPosition(j * a, i * a);
                sprite.setScale(0.08f, 0.08f);
                break;
            }
            
            mWindow.draw(sprite);
        }
    }
}