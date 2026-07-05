#include "ThemeManager.h"

Theme ThemeManager::currentTheme =
{
    sf::Color(35,35,35),

    sf::Color(240,217,181),
    sf::Color(181,136,99),

    sf::Color(255,215,0),

    sf::Color(120,180,255),

    sf::Color(45,45,45),
    sf::Color::White
};

void ThemeManager::setTheme(ThemeType type)
{
    switch (type)
    {
    case ThemeType::Classic:

        currentTheme =
        {
            sf::Color(35,35,35),

            sf::Color(240,217,181),
            sf::Color(181,136,99),

            sf::Color(255,215,0),

            sf::Color(120,180,255),

            sf::Color(45,45,45),
            sf::Color::White
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