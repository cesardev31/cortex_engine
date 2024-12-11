#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    std::function<void()> callback;
    bool isHovered;

public:
    Button(const sf::Vector2f &position, const sf::Vector2f &size,
           const std::string &buttonText, const std::function<void()> &onClick,
           const sf::Color &baseColor = sf::Color(70, 70, 70))
        : callback(onClick), isHovered(false)
    {
        if (!font.loadFromFile("resources/fonts/Roboto/Roboto-Bold.ttf"))
        {
            throw std::runtime_error("No se pudo cargar la fuente");
        }

        // Estilo moderno para el botón
        shape.setPosition(position);
        shape.setSize(size);
        shape.setFillColor(baseColor);

        // Efecto de borde suave
        shape.setOutlineThickness(1.0f);
        shape.setOutlineColor(sf::Color(0, 0, 0, 50));

        // Texto moderno
        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(16);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::White);

        // Centrar texto
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            position.x + (size.x - textBounds.width) / 2,
            position.y + (size.y - textBounds.height) / 2 - 2);
    }

    void handleEvent(const sf::Event &event, const sf::RenderWindow &window)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x),
                               static_cast<float>(mousePos.y));

        bool wasHovered = isHovered;
        isHovered = shape.getGlobalBounds().contains(mousePosF);

        // Efecto hover más suave
        sf::Color currentColor = shape.getFillColor();
        if (isHovered && !wasHovered)
        {
            shape.setFillColor(sf::Color(
                currentColor.r + 20,
                currentColor.g + 20,
                currentColor.b + 20));
        }
        else if (!isHovered && wasHovered)
        {
            shape.setFillColor(sf::Color(
                currentColor.r - 20,
                currentColor.g - 20,
                currentColor.b - 20));
        }

        // Manejar clic
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left &&
            isHovered)
        {
            callback();
        }
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
        window.draw(text);
    }
};
