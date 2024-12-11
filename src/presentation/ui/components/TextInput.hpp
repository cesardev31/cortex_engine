#pragma once
#include <SFML/Graphics.hpp>

class TextInput
{
private:
    sf::RectangleShape background;
    sf::Text text;
    sf::Text label;
    bool isFocused = false;

public:
    TextInput(const sf::Font &font, const std::string &labelText, const sf::Vector2f &size)
    {
        // Configuración del input
        background.setSize(size);
        background.setFillColor(sf::Color(60, 60, 65));
        background.setOutlineColor(sf::Color(70, 70, 75));
        background.setOutlineThickness(1.0f);

        // Configuración del texto
        text.setFont(font);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::White);

        // Configuración de la etiqueta
        label.setFont(font);
        label.setString(labelText);
        label.setCharacterSize(16);
        label.setFillColor(sf::Color::White);
    }

    void setPosition(const sf::Vector2f &pos);
    void handleEvent(const sf::Event &event);
    void draw(sf::RenderWindow &window);
    std::string getValue() const;
    void setValue(const std::string &value);
    bool hasFocus() const { return isFocused; }
};