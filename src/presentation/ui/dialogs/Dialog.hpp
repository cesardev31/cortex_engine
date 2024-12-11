#pragma once
#include <SFML/Graphics.hpp>

class Dialog
{
protected:
    sf::RectangleShape background;
    sf::RectangleShape modal;
    bool isVisible = false;

    virtual void initializeComponents() = 0;
    virtual void updatePositions() = 0;

public:
    Dialog(const sf::Vector2f &size)
    {
        background.setSize(sf::Vector2f(800, 600));
        background.setFillColor(sf::Color(0, 0, 0, 180));

        modal.setSize(size);
        modal.setFillColor(sf::Color(45, 45, 48));
        modal.setOutlineColor(sf::Color(60, 60, 65));
        modal.setOutlineThickness(1.0f);
    }

    virtual void show() { isVisible = true; }
    virtual void hide() { isVisible = false; }
    virtual void handleEvent(const sf::Event &event, const sf::RenderWindow &window) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    bool getVisible() const { return isVisible; }
};