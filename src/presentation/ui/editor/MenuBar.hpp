#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>

class MenuItem
{
public:
    std::string label;
    std::vector<MenuItem> subItems;
    std::function<void()> action;
    bool isOpen = false;

    MenuItem(const std::string &l, std::function<void()> a = nullptr)
        : label(l), action(a) {}
};

class MenuBar
{
private:
    sf::RenderWindow &window;
    sf::Font &font;
    std::vector<MenuItem> menuItems;
    sf::RectangleShape background;
    float itemHeight = 25.0f;
    float itemPadding = 10.0f;

    const sf::Color MENU_BG_COLOR{45, 45, 48};
    const sf::Color MENU_HOVER_COLOR{62, 62, 66};
    const sf::Color TEXT_COLOR{200, 200, 200};

public:
    MenuBar(sf::RenderWindow &win, sf::Font &f) : window(win), font(f)
    {
        background.setSize(sf::Vector2f(window.getSize().x, itemHeight));
        background.setFillColor(MENU_BG_COLOR);

        initializeMenuItems();
    }

    void draw()
    {
        window.draw(background);

        float x = itemPadding;
        for (const auto &item : menuItems)
        {
            sf::Text text;
            text.setFont(font);
            text.setString(item.label);
            text.setCharacterSize(14);
            text.setFillColor(TEXT_COLOR);
            text.setPosition(x, (itemHeight - text.getLocalBounds().height) / 2);
            window.draw(text);

            x += text.getLocalBounds().width + itemPadding * 2;
        }
    }

    void handleEvent(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            handleClick(event.mouseButton);
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            handleHover({event.mouseMove.x, event.mouseMove.y});
        }
    }

private:
    void initializeMenuItems()
    {
        // Menú Archivo
        MenuItem fileMenu("Archivo");
        fileMenu.subItems = {
            MenuItem("Nuevo Proyecto", []() { /* TODO */ }),
            MenuItem("Abrir Proyecto", []() { /* TODO */ }),
            MenuItem("Guardar", []() { /* TODO */ }),
            MenuItem("Guardar Como", []() { /* TODO */ }),
            MenuItem("Salir", []() { /* TODO */ })};

        // Menú Editar
        MenuItem editMenu("Editar");
        editMenu.subItems = {
            MenuItem("Deshacer", []() { /* TODO */ }),
            MenuItem("Rehacer", []() { /* TODO */ }),
            MenuItem("Copiar", []() { /* TODO */ }),
            MenuItem("Pegar", []() { /* TODO */ })};

        // Menú Ver
        MenuItem viewMenu("Ver");
        viewMenu.subItems = {
            MenuItem("Mostrar Grid", []() { /* TODO */ }),
            MenuItem("Mostrar Reglas", []() { /* TODO */ }),
            MenuItem("Zoom In", []() { /* TODO */ }),
            MenuItem("Zoom Out", []() { /* TODO */ })};

        // Menú Depurar
        MenuItem debugMenu("Depurar");
        debugMenu.subItems = {
            MenuItem("Iniciar", []() { /* TODO */ }),
            MenuItem("Pausar", []() { /* TODO */ }),
            MenuItem("Paso a Paso", []() { /* TODO */ })};

        menuItems = {fileMenu, editMenu, viewMenu, debugMenu};
    }

    void handleClick(const sf::Event::MouseButtonEvent &mouseButton)
    {
        // TODO: Implementar lógica de click
    }

    void handleHover(sf::Vector2i mousePos)
    {
        // TODO: Implementar lógica de hover
    }
};