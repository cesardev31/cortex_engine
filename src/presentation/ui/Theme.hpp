#pragma once
#include <SFML/Graphics.hpp>

struct Theme
{
    struct Colors
    {
        sf::Color primary;
        sf::Color secondary;
        sf::Color background;
        sf::Color text;
        sf::Color error;
    } colors;

    struct Fonts
    {
        std::string regular;
        std::string bold;
        std::string light;
    } fonts;

    struct Sizes
    {
        float buttonHeight;
        float inputHeight;
        float spacing;
    } sizes;

    static Theme &getInstance()
    {
        static Theme instance;
        return instance;
    }
};