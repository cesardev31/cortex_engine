#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <variant>
#include <string>

class Property
{
public:
    std::string name;
    std::variant<int, float, std::string, bool> value;

    Property(const std::string &n, int v)
        : name(n), value(v) {}

    Property(const std::string &n, float v)
        : name(n), value(v) {}

    Property(const std::string &n, const std::string &v)
        : name(n), value(v) {}

    Property(const std::string &n, bool v)
        : name(n), value(v) {}
};

class Inspector
{
private:
    sf::RenderWindow &window;
    sf::Font &font;
    sf::RectangleShape background;
    std::vector<Property> properties;

    const sf::Color BG_COLOR{45, 45, 48};
    const sf::Color PROPERTY_BG_COLOR{38, 38, 38};
    const sf::Color TEXT_COLOR{200, 200, 200};

public:
    Inspector(sf::RenderWindow &win, sf::Font &f)
        : window(win), font(f)
    {
        background.setSize(sf::Vector2f(250, window.getSize().y - 65));
        background.setPosition(window.getSize().x - 250, 40);
        background.setFillColor(BG_COLOR);

        properties.emplace_back("Posición X", 0.0f);
        properties.emplace_back("Posición Y", 0.0f);
        properties.emplace_back("Rotación", 0.0f);
        properties.emplace_back("Escala", 1.0f);
        properties.emplace_back("Visible", true);
    }

    void setTarget(void *target)
    {
        properties.clear();
        if (target)
        {
            // TODO: Reflejar propiedades del objeto seleccionado
        }
    }

    void draw()
    {
        window.draw(background);

        sf::Text title;
        title.setFont(font);
        title.setString("Inspector");
        title.setCharacterSize(14);
        title.setFillColor(TEXT_COLOR);
        title.setPosition(window.getSize().x - 240, 45);
        window.draw(title);

        float y = 70;
        for (const auto &prop : properties)
        {
            drawProperty(prop, y);
            y += 25;
        }
    }

    void handleEvent(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            handleClick(event.mouseButton);
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            handleKeyPress(event.key);
        }
    }

private:
    void drawProperty(const Property &prop, float y)
    {
        sf::Text nameText;
        nameText.setFont(font);
        nameText.setString(prop.name);
        nameText.setCharacterSize(12);
        nameText.setFillColor(TEXT_COLOR);
        nameText.setPosition(window.getSize().x - 240, y);
        window.draw(nameText);

        sf::Text valueText;
        valueText.setFont(font);
        valueText.setString(getPropertyValueString(prop.value));
        valueText.setCharacterSize(12);
        valueText.setFillColor(TEXT_COLOR);
        valueText.setPosition(window.getSize().x - 100, y);
        window.draw(valueText);
    }

    std::string getPropertyValueString(const std::variant<int, float, std::string, bool> &value)
    {
        return std::visit([](auto &&arg) -> std::string
                          {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, bool>)
                return arg ? "true" : "false";
            else if constexpr (std::is_same_v<T, int> || std::is_same_v<T, float>)
                return std::to_string(arg);
            else
                return arg; }, value);
    }

    void handleClick(const sf::Event::MouseButtonEvent &mouseButton)
    {
        // TODO: Implementar lógica de click
    }

    void handleKeyPress(const sf::Event::KeyEvent &key)
    {
        // TODO: Implementar lógica de teclado
    }
};