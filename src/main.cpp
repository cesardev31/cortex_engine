#include <iostream>
#include <SFML/Graphics.hpp>
#include "core/Engine.hpp"
#include "presentation/ui/ProjectDialog.hpp"
#include <filesystem>

class GameState
{
private:
    sf::RenderWindow window;
    ProjectDialog projectDialog;
    sf::View baseView;
    float baseWidth = 800.0f;
    float baseHeight = 600.0f;

public:
    GameState()
        : projectDialog(window)
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        window.create(sf::VideoMode(baseWidth, baseHeight), "Cortex Engine", sf::Style::Default, settings);
        window.setFramerateLimit(60);

        // Cargar y establecer el ícono
        sf::Image icon;
        if (icon.loadFromFile("resources/icons/cortex.png"))
        {
            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
            std::cout << "Ícono cargado correctamente" << std::endl;
        }
        else
        {
            std::cerr << "Error al cargar el ícono" << std::endl;
        }

        // Inicializar la vista base
        baseView.setSize(baseWidth, baseHeight);
        baseView.setCenter(baseWidth / 2, baseHeight / 2);
        window.setView(baseView);
    }

    void run()
    {
        while (window.isOpen())
        {
            handleEvents();
            update();
            render();
        }
    }

private:
    void handleEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
            {
                // Calcular el factor de escala manteniendo la proporción
                float scaleX = event.size.width / baseWidth;
                float scaleY = event.size.height / baseHeight;
                float scale = std::min(scaleX, scaleY);

                // Calcular el nuevo viewport
                float viewportWidth = (baseWidth * scale) / event.size.width;
                float viewportHeight = (baseHeight * scale) / event.size.height;
                float viewportLeft = (1.0f - viewportWidth) / 2.0f;
                float viewportTop = (1.0f - viewportHeight) / 2.0f;

                // Aplicar el nuevo viewport
                baseView.setViewport(sf::FloatRect(viewportLeft, viewportTop, viewportWidth, viewportHeight));
                window.setView(baseView);
            }

            projectDialog.handleEvent(event, window);
        }
    }

    void update()
    {
        // Actualizar lógica
    }

    void render()
    {
        window.clear(sf::Color(38, 38, 38));
        window.setView(baseView);
        projectDialog.draw(window);
        window.display();
    }
};

std::string getResourcePath(const std::string &resource)
{
    return std::filesystem::current_path().parent_path().string() + "/resources/" + resource;
}

int main()
{
    try
    {
        GameState game;
        game.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}