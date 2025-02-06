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
                // Ajustar la vista al nuevo tamaño de la ventana
                float aspectRatio = baseWidth / baseHeight;
                float windowRatio = static_cast<float>(event.size.width) / static_cast<float>(event.size.height);
                float viewWidth = baseWidth;
                float viewHeight = baseHeight;

                if (windowRatio > aspectRatio) {
                    viewWidth = viewHeight * windowRatio;
                } else {
                    viewHeight = viewWidth / windowRatio;
                }

                // Centrar la vista
                baseView.setSize(viewWidth, viewHeight);
                baseView.setCenter(viewWidth / 2.0f, viewHeight / 2.0f);
                
                // Ajustar el viewport para cubrir toda la ventana
                baseView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
                
                // Aplicar la vista actualizada
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