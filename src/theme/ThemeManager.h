#pragma once

#include "Theme.h"

enum class ThemeType
{
    Classic,
    Dark,
    Ocean,
    Sakura,
    Emerald,
    Lava,
    Ice,
    PurpleGalaxy,
    Gold,
    Rainbow
};

class ThemeManager
{
public:

    static void setTheme(ThemeType type);

    static const Theme& getTheme();

private:

    static Theme currentTheme;
};