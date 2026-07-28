#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "../engine/pieces/Piece.h"
#include "../engine/position/Position.h"

class Board;

class Renderer
{
public:
    Renderer();

    void draw(
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
    );

private:
    void drawBoard(
        sf::RenderWindow& window
    );

    void drawLastMove(
        sf::RenderWindow& window,
        bool hasLastMove,
        const Position& from,
        const Position& to
    );

    void drawSelectedSquare(
        sf::RenderWindow& window,
        bool pieceSelected,
        const Position& selectedSquare
    );

    void drawHighlights(
        sf::RenderWindow& window,
        const std::vector<Position>& highlightedSquares
    );

    void drawPieces(
        sf::RenderWindow& window,
        const Board& board
    );

    void drawPromotionPanel(
        sf::RenderWindow& window,
        bool promotionPending,
        PieceColor promotionColor
    );

    std::wstring getPieceSymbol(
        PieceType type,
        PieceColor color
    ) const;

private:
    sf::Font font;
};