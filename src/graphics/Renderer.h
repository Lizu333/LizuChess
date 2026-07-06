#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../engine/position/Position.h"

class Board;

class Renderer
{
public:
    Renderer();

    void draw(
        sf::RenderWindow& window,
        const Board& board,
        const std::vector<Position>& highlightedSquares
    );

private:
    void drawBoard(sf::RenderWindow& window);

    void drawHighlights(
        sf::RenderWindow& window,
        const std::vector<Position>& highlightedSquares
    );

    void drawPieces(sf::RenderWindow& window, const Board& board);

private:
    sf::Font font;
};