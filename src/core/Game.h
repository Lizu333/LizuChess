#pragma once

#include <SFML/Graphics.hpp>

#include "../graphics/Renderer.h"
#include "../engine/chessengine/ChessEngine.h"

class Game
{
public:
    Game();

    void run();

private:
    void processEvents();
    void update();
    void render();

private:
    sf::RenderWindow window;
    ChessEngine chessEngine;
    Renderer renderer;
};