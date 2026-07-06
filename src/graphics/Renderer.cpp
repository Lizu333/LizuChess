#include "Renderer.h"

#include <stdexcept>
#include <string>

#include "../engine/board/Board.h"
#include "../engine/pieces/Piece.h"
#include "../theme/ThemeManager.h"

Renderer::Renderer()
{
    if (!font.openFromFile("C:/Windows/Fonts/seguisym.ttf"))
    {
        throw std::runtime_error("Failed to load font.");
    }
}

void Renderer::draw(
    sf::RenderWindow& window,
    const Board& board,
    const std::vector<Position>& highlightedSquares
)
{
    drawBoard(window);
    drawHighlights(window, highlightedSquares);
    drawPieces(window, board);
}

void Renderer::drawBoard(sf::RenderWindow& window)
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

void Renderer::drawHighlights(
    sf::RenderWindow& window,
    const std::vector<Position>& highlightedSquares
)
{
    constexpr float tileSize = 96.f;
    constexpr float circleRadius = 14.f;

    for (const Position& square : highlightedSquares)
    {
        sf::CircleShape circle(circleRadius);

        circle.setFillColor(sf::Color(0, 180, 0, 160));

        circle.setPosition({
            square.getX() * tileSize + tileSize / 2.f - circleRadius,
            square.getY() * tileSize + tileSize / 2.f - circleRadius
            });

        window.draw(circle);
    }
}

void Renderer::drawPieces(sf::RenderWindow& window, const Board& board)
{
    constexpr float tileSize = 96.f;

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Position position(x, y);
            Piece piece = board.getPiece(position);

            if (piece.isEmpty())
                continue;

            std::wstring symbol;

            if (piece.getColor() == PieceColor::White)
            {
                switch (piece.getType())
                {
                case PieceType::King:   symbol = L"♔"; break;
                case PieceType::Queen:  symbol = L"♕"; break;
                case PieceType::Rook:   symbol = L"♖"; break;
                case PieceType::Bishop: symbol = L"♗"; break;
                case PieceType::Knight: symbol = L"♘"; break;
                case PieceType::Pawn:   symbol = L"♙"; break;
                default:                symbol = L""; break;
                }
            }
            else
            {
                switch (piece.getType())
                {
                case PieceType::King:   symbol = L"♚"; break;
                case PieceType::Queen:  symbol = L"♛"; break;
                case PieceType::Rook:   symbol = L"♜"; break;
                case PieceType::Bishop: symbol = L"♝"; break;
                case PieceType::Knight: symbol = L"♞"; break;
                case PieceType::Pawn:   symbol = L"♟"; break;
                default:                symbol = L""; break;
                }
            }

            sf::Text text(font);
            text.setString(symbol);
            text.setCharacterSize(72);

            text.setFillColor(
                piece.getColor() == PieceColor::White
                ? sf::Color::White
                : sf::Color::Black
            );

            text.setPosition({
                x * tileSize + 20.f,
                y * tileSize + 5.f
                });

            window.draw(text);
        }
    }
}