#include "Renderer.h"

#include <stdexcept>
#include <string>

#include "../engine/board/Board.h"
#include "../theme/ThemeManager.h"

Renderer::Renderer()
{
    if (!font.openFromFile(
        "C:/Windows/Fonts/seguisym.ttf"
    ))
    {
        throw std::runtime_error(
            "Failed to load chess font."
        );
    }
}

void Renderer::draw(
    sf::RenderWindow& window,
    const Board& board,
    const std::vector<Position>& highlightedSquares,
    bool pieceSelected,
    const Position& selectedSquare,
    bool hasLastMove,
    const Position& lastMoveFrom,
    const Position& lastMoveTo,
    bool promotionPending,
    PieceColor promotionColor
)
{
    drawBoard(window);

    drawLastMove(
        window,
        hasLastMove,
        lastMoveFrom,
        lastMoveTo
    );

    drawSelectedSquare(
        window,
        pieceSelected,
        selectedSquare
    );

    drawHighlights(
        window,
        highlightedSquares
    );

    drawPieces(
        window,
        board
    );

    drawPromotionPanel(
        window,
        promotionPending,
        promotionColor
    );
}

void Renderer::drawBoard(
    sf::RenderWindow& window
)
{
    const Theme& theme =
        ThemeManager::getTheme();

    constexpr int boardSize = 8;
    constexpr float tileSize = 96.f;

    sf::RectangleShape tile(
        { tileSize, tileSize }
    );

    for (int y = 0; y < boardSize; y++)
    {
        for (int x = 0; x < boardSize; x++)
        {
            tile.setPosition(
                {
                    x * tileSize,
                    y * tileSize
                }
            );

            tile.setFillColor(
                ((x + y) % 2 == 0)
                ? theme.lightSquare
                : theme.darkSquare
            );

            window.draw(tile);
        }
    }
}

void Renderer::drawLastMove(
    sf::RenderWindow& window,
    bool hasLastMove,
    const Position& from,
    const Position& to
)
{
    if (!hasLastMove)
        return;

    const Theme& theme =
        ThemeManager::getTheme();

    constexpr float tileSize = 96.f;

    sf::RectangleShape highlight(
        { tileSize, tileSize }
    );

    highlight.setFillColor(
        theme.lastMoveHighlight
    );

    highlight.setPosition(
        {
            from.getX() * tileSize,
            from.getY() * tileSize
        }
    );

    window.draw(highlight);

    highlight.setPosition(
        {
            to.getX() * tileSize,
            to.getY() * tileSize
        }
    );

    window.draw(highlight);
}

void Renderer::drawSelectedSquare(
    sf::RenderWindow& window,
    bool pieceSelected,
    const Position& selectedSquare
)
{
    if (!pieceSelected)
        return;

    const Theme& theme =
        ThemeManager::getTheme();

    constexpr float tileSize = 96.f;

    sf::RectangleShape border(
        { tileSize, tileSize }
    );

    border.setPosition(
        {
            selectedSquare.getX() * tileSize,
            selectedSquare.getY() * tileSize
        }
    );

    border.setFillColor(
        sf::Color::Transparent
    );

    border.setOutlineThickness(-6.f);

    border.setOutlineColor(
        theme.selectedSquareBorder
    );

    window.draw(border);
}

void Renderer::drawHighlights(
    sf::RenderWindow& window,
    const std::vector<Position>& highlightedSquares
)
{
    const Theme& theme =
        ThemeManager::getTheme();

    constexpr float tileSize = 96.f;
    constexpr float circleRadius = 18.f;

    for (const Position& square :
        highlightedSquares)
    {
        sf::CircleShape circle(
            circleRadius
        );

        circle.setFillColor(
            theme.legalMoveHighlight
        );

        circle.setPosition(
            {
                square.getX() * tileSize +
                    tileSize / 2.f -
                    circleRadius,

                square.getY() * tileSize +
                    tileSize / 2.f -
                    circleRadius
            }
        );

        window.draw(circle);
    }
}

void Renderer::drawPieces(
    sf::RenderWindow& window,
    const Board& board
)
{
    constexpr float tileSize = 96.f;

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            const Position position(x, y);

            const Piece piece =
                board.getPiece(position);

            if (piece.isEmpty())
                continue;

            const std::wstring symbol =
                getPieceSymbol(
                    piece.getType(),
                    piece.getColor()
                );

            sf::Text text(font);

            text.setString(symbol);
            text.setCharacterSize(72);

            text.setFillColor(
                piece.getColor() ==
                PieceColor::White
                ? sf::Color::White
                : sf::Color::Black
            );

            text.setPosition(
                {
                    x * tileSize + 20.f,
                    y * tileSize + 5.f
                }
            );

            window.draw(text);
        }
    }
}

void Renderer::drawPromotionPanel(
    sf::RenderWindow& window,
    bool promotionPending,
    PieceColor promotionColor
)
{
    if (!promotionPending)
        return;

    const Theme& theme =
        ThemeManager::getTheme();

    constexpr float panelX = 800.f;
    constexpr float panelY = 130.f;
    constexpr float panelWidth = 216.f;
    constexpr float panelHeight = 440.f;

    constexpr float buttonX = 820.f;
    constexpr float firstButtonY = 190.f;

    constexpr float buttonSize = 64.f;
    constexpr float buttonSpacing = 20.f;

    sf::RectangleShape panel(
        { panelWidth, panelHeight }
    );

    panel.setPosition(
        { panelX, panelY }
    );

    panel.setFillColor(
        theme.panelBackground
    );

    panel.setOutlineThickness(3.f);

    panel.setOutlineColor(
        theme.selectedSquareBorder
    );

    window.draw(panel);

    sf::Text heading(font);

    heading.setString(
        "Promotion"
    );

    heading.setCharacterSize(24);

    heading.setFillColor(
        theme.panelText
    );

    heading.setPosition(
        { 824.f, 145.f }
    );

    window.draw(heading);

    constexpr PieceType pieceTypes[4] =
    {
        PieceType::Queen,
        PieceType::Rook,
        PieceType::Bishop,
        PieceType::Knight
    };

    for (int index = 0; index < 4; index++)
    {
        const float buttonY =
            firstButtonY +
            index *
            (buttonSize + buttonSpacing);

        sf::RectangleShape button(
            { buttonSize, buttonSize }
        );

        button.setPosition(
            { buttonX, buttonY }
        );

        button.setFillColor(
            sf::Color(75, 75, 75)
        );

        button.setOutlineThickness(2.f);

        button.setOutlineColor(
            theme.selectedSquareBorder
        );

        window.draw(button);

        const std::wstring symbol =
            getPieceSymbol(
                pieceTypes[index],
                promotionColor
            );

        sf::Text pieceText(font);

        pieceText.setString(symbol);
        pieceText.setCharacterSize(48);

        pieceText.setFillColor(
            promotionColor ==
            PieceColor::White
            ? sf::Color::White
            : sf::Color::Black
        );

        pieceText.setPosition(
            {
                buttonX + 10.f,
                buttonY - 2.f
            }
        );

        window.draw(pieceText);
    }
}

std::wstring Renderer::getPieceSymbol(
    PieceType type,
    PieceColor color
) const
{
    if (color == PieceColor::White)
    {
        switch (type)
        {
        case PieceType::King:
            return L"♔";

        case PieceType::Queen:
            return L"♕";

        case PieceType::Rook:
            return L"♖";

        case PieceType::Bishop:
            return L"♗";

        case PieceType::Knight:
            return L"♘";

        case PieceType::Pawn:
            return L"♙";

        default:
            return L"";
        }
    }

    if (color == PieceColor::Black)
    {
        switch (type)
        {
        case PieceType::King:
            return L"♚";

        case PieceType::Queen:
            return L"♛";

        case PieceType::Rook:
            return L"♜";

        case PieceType::Bishop:
            return L"♝";

        case PieceType::Knight:
            return L"♞";

        case PieceType::Pawn:
            return L"♟";

        default:
            return L"";
        }
    }

    return L"";
}