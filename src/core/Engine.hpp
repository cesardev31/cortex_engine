#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class Engine
{
private:
    sf::RenderWindow &window;
    bool initialized;

public:
    Engine(sf::RenderWindow &window) : window(window), initialized(false) {}

    bool init()
    {
        // Configurar contexto OpenGL
        window.setActive(true);

        // Configuración básica de OpenGL
        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        initialized = true;
        return true;
    }

    void beginFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void endFrame()
    {
        window.display();
    }

    void cleanup()
    {
        window.setActive(false);
    }

    bool isInitialized() const { return initialized; }
};