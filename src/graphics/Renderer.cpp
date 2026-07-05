#include "Renderer.h"

#include "../board/Board.h"
#include "../theme/ThemeManager.h"

Renderer::Renderer()
{
}

void Renderer::draw(sf::RenderWindow& window, const Board& board)
{
    drawBoard(window, board);
}

void Renderer::drawBoard(sf::RenderWindow& window, const Board&)
{
    const Theme& theme = ThemeManager::getTheme();

    constexpr int boardSize = 8;
    constexpr float tileSize = 96.f;

    sf::RectangleShape tile({ tileSize, tileSize });

    for (int y = 0; y < boardSize; y++)
    {
        for (int x = 0; x < boardSize; x++)
        {
            tile.setPosition({
                x * tileSize,
                y * tileSize
                });

            tile.setFillColor(
                ((x + y) % 2 == 0)
                ? theme.lightSquare
                : theme.darkSquare
            );

            window.draw(tile);
        }
    }
}