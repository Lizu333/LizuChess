#pragma once

#include <SFML/Graphics.hpp>

class Board;

class Renderer
{
public:
    Renderer();

    void draw(sf::RenderWindow& window, const Board& board);

private:
    void drawBoard(sf::RenderWindow& window);
    void drawPieces(sf::RenderWindow& window, const Board& board);

    sf::Font font;
};