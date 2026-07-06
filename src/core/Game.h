#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../graphics/Renderer.h"

#include "../engine/chessengine/ChessEngine.h"
#include "../engine/move/Move.h"
#include "../engine/position/Position.h"

class Game
{
public:
    Game();

    void run();

private:
    void processEvents();
    void update();
    void render();

    void handleMouseClick(int mouseX, int mouseY);

private:
    sf::RenderWindow window;

    ChessEngine chessEngine;
    Renderer renderer;

    bool pieceSelected = false;
    Position selectedSquare;

    std::vector<Position> highlightedSquares;
};