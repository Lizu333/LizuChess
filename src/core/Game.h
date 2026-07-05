#pragma once

#include <SFML/Graphics.hpp>
#include "../board/Board.h"
#include "../graphics/Renderer.h"

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

    Renderer renderer;
    Board board;
};