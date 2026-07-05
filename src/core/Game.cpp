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
            window.close();
    }
}

void Game::update()
{
}

void Game::render()
{
    const Theme& theme = ThemeManager::getTheme();

    window.clear(theme.background);

    renderer.draw(window, board);

    window.display();
}