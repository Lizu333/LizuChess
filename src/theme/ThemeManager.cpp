#include "ThemeManager.h"

Theme ThemeManager::currentTheme =
{
    sf::Color(35, 35, 35),          //background

    sf::Color(240, 217, 181),       //lightSquare
    sf::Color(181, 136, 99),        //darkSquare

    sf::Color(255, 215, 0),         //selectedSquare
    sf::Color(120, 180, 255),       //legalMove

    sf::Color(45, 45, 45),          //panelBackground
    sf::Color::White,               //panelText

    sf::Color(255, 230, 120, 110),  //lastMoveHighlight
    sf::Color(170, 80, 255, 255),   //selectedSquareBorder
    sf::Color(80, 220, 120, 190)    //legalMoveHighlight
};

void ThemeManager::setTheme(ThemeType type)
{
    switch (type)
    {
    case ThemeType::Classic:
        currentTheme =
        {
            sf::Color(35, 35, 35),

            sf::Color(240, 217, 181),
            sf::Color(181, 136, 99),

            sf::Color(255, 215, 0),
            sf::Color(120, 180, 255),

            sf::Color(45, 45, 45),
            sf::Color::White,

            sf::Color(255, 230, 120, 110),
            sf::Color(170, 80, 255, 255),
            sf::Color(80, 220, 120, 190)
        };
        break;

    default:
        break;
    }
}

const Theme& ThemeManager::getTheme()
{
    return currentTheme;
}