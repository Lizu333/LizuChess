#pragma once

#include <SFML/Graphics.hpp>

struct Theme
{
    sf::Color background;

    sf::Color lightSquare;
    sf::Color darkSquare;

    sf::Color selectedSquare;
    sf::Color legalMove;

    sf::Color panelBackground;
    sf::Color panelText;

    sf::Color lastMoveHighlight;
    sf::Color selectedSquareBorder;
    sf::Color legalMoveHighlight;
};