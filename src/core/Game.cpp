#include "Game.h"

#include "../theme/ThemeManager.h"

Game::Game()
    : window(sf::VideoMode({ 1048, 768 }), "LizuChess")
{
    window.setFramerateLimit(60);
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    while (const auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto* mouse =
            event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouse->button == sf::Mouse::Button::Left)
            {
                handleMouseClick(
                    mouse->position.x,
                    mouse->position.y
                );
            }
        }
    }
}

void Game::update()
{
}

void Game::render()
{
    const Theme& theme = ThemeManager::getTheme();

    window.clear(theme.background);

    renderer.draw(window, chessEngine.getBoard());

    window.display();
}

void Game::handleMouseClick(int mouseX, int mouseY)
{
    constexpr float tileSize = 96.f;

    int boardX = static_cast<int>(mouseX / tileSize);
    int boardY = static_cast<int>(mouseY / tileSize);

    Position clickedSquare(boardX, boardY);

    if (!chessEngine.getBoard().isInsideBoard(clickedSquare))
        return;

    if (!pieceSelected)
    {
        Piece piece = chessEngine.getBoard().getPiece(clickedSquare);

        if (piece.isEmpty())
            return;

        if (piece.getColor() != chessEngine.getGameState().getSideToMove())
            return;

        selectedSquare = clickedSquare;
        pieceSelected = true;
        return;
    }

    Move move(selectedSquare, clickedSquare);

    chessEngine.makeMove(move);

    pieceSelected = false;
}