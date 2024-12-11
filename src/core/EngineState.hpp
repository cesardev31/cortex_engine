#pragma once
#include <SFML/Graphics.hpp>
#include "Engine.hpp"
#include "../domain/entities/Project.hpp"
#include "../infrastructure/rendering/Renderer.hpp"
#include <algorithm>
#include <stdexcept>
#include "../presentation/ui/editor/EditorUI.hpp"

class EngineState
{
private:
    sf::RenderWindow &window;
    Engine engine;
    Domain::ProjectInfo currentProject;
    Infrastructure::SFMLRenderer renderer;
    sf::View editorView;

    // Variables de estado del editor
    bool isPlaying = false;
    bool showGrid = true;
    float zoomLevel = 1.0f;

    EditorUI editorUI;

public:
    EngineState(sf::RenderWindow &win, const Domain::ProjectInfo &project)
        : window(win), engine(win), currentProject(project), renderer(win), editorUI(win)
    {
        initializeEngine();
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
    void initializeEngine()
    {
        if (!engine.init())
        {
            throw std::runtime_error("Error al inicializar el motor");
        }

        // Configurar la vista del editor
        editorView = window.getDefaultView();

        // Cargar la configuración del proyecto
        loadProjectConfig();
    }

    void handleEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                handleKeyPress(event.key);
            }
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                handleZoom(event.mouseWheelScroll);
            }
            editorUI.handleEvent(event);
        }
    }

    void handleKeyPress(const sf::Event::KeyEvent &key)
    {
        if (key.control)
        {
            switch (key.code)
            {
            case sf::Keyboard::S:
                saveProject();
                break;
            case sf::Keyboard::P:
                togglePlayMode();
                break;
            case sf::Keyboard::G:
                showGrid = !showGrid;
                break;
                // Agregar más atajos de teclado
            }
        }
    }

    void handleZoom(const sf::Event::MouseWheelScrollEvent &scroll)
    {
        if (scroll.delta > 0)
            zoomLevel *= 1.1f;
        else if (scroll.delta < 0)
            zoomLevel *= 0.9f;

        zoomLevel = std::clamp(zoomLevel, 0.1f, 5.0f);
        editorView.setSize(window.getDefaultView().getSize());
        editorView.zoom(zoomLevel);
    }

    void update()
    {
        if (isPlaying)
        {
            // Actualizar la lógica del juego cuando está en modo play
            updateGameLogic();
        }
        // Actualizar la lógica del editor
        updateEditor();
    }

    void render()
    {
        window.clear(sf::Color(38, 38, 38)); // Color de fondo del editor

        if (isPlaying)
        {
            renderGame();
        }
        else
        {
            renderEditor();
        }

        window.display();
    }

    void renderEditor()
    {
        editorUI.draw();
    }

    void renderGame()
    {
        // Renderizar el juego en ejecución
        engine.beginFrame();
        // Renderizar la escena actual
        engine.endFrame();
    }

    void drawGrid()
    {
        // Implementar el dibujado de la cuadrícula
        // TODO: Implementar
    }

    void drawEditorUI()
    {
        // Implementar la interfaz del editor
        // TODO: Implementar
    }

    void updateGameLogic()
    {
        // Actualizar la lógica del juego
        // TODO: Implementar
    }

    void updateEditor()
    {
        // Actualizar la lógica del editor
        // TODO: Implementar
    }

    void togglePlayMode()
    {
        isPlaying = !isPlaying;
        if (isPlaying)
        {
            // Inicializar el modo de juego
        }
        else
        {
            // Restaurar el modo de edición
        }
    }

    void saveProject()
    {
        // Implementar guardado del proyecto
        // TODO: Implementar
    }

    void loadProjectConfig()
    {
        // Cargar la configuración del proyecto
        // TODO: Implementar
    }
};