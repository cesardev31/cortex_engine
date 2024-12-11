#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "../Button.hpp"
#include "../../../core/EngineState.hpp"
#include "MenuBar.hpp"
#include "FileExplorer.hpp"
#include "Inspector.hpp"

enum class EditorTool
{
    Select,
    AddSprite,
};

class EditorUI
{
private:
    sf::RenderWindow &window;
    sf::Font font;

    // Paneles principales
    sf::RectangleShape topBar;
    sf::RectangleShape leftPanel;
    sf::RectangleShape rightPanel;
    sf::RectangleShape bottomBar;

    // Área de trabajo (donde se muestra la escena)
    sf::RectangleShape workArea;

    // Botones de herramientas
    std::vector<std::unique_ptr<Button>> toolButtons;

    // Estado actual
    bool isPlaying = false;
    float zoom = 1.0f;
    sf::Vector2f panOffset{0, 0};

    // Colores del tema
    const sf::Color PANEL_COLOR{45, 45, 48};
    const sf::Color DARKER_PANEL_COLOR{30, 30, 33};
    const sf::Color ACCENT_COLOR{0, 122, 204};
    const sf::Color WORK_AREA_COLOR{38, 38, 38};

    MenuBar menuBar;
    FileExplorer fileExplorer;
    Inspector inspector;

public:
    EditorUI(sf::RenderWindow &win)
        : window(win), menuBar(win, font), fileExplorer(win, font), inspector(win, font)
    {
        if (!font.loadFromFile("resources/fonts/Roboto/Roboto-Regular.ttf"))
        {
            throw std::runtime_error("No se pudo cargar la fuente");
        }

        initializeLayout();
        createToolButtons();
    }

    void draw()
    {
        drawPanels();
        menuBar.draw();
        fileExplorer.draw();
        inspector.draw();
        drawToolButtons();
        drawStatusBar();
        drawGrid();
    }

    void handleEvent(const sf::Event &event)
    {
        menuBar.handleEvent(event);
        fileExplorer.handleEvent(event);
        inspector.handleEvent(event);

        for (auto &button : toolButtons)
        {
            button->handleEvent(event, window);
        }

        handlePanning(event);
        handleZoom(event);
    }

private:
    void initializeLayout()
    {
        // Configurar barra superior
        topBar.setSize(sf::Vector2f(window.getSize().x, 40));
        topBar.setFillColor(PANEL_COLOR);

        // Panel izquierdo (herramientas)
        leftPanel.setSize(sf::Vector2f(200, window.getSize().y - 80));
        leftPanel.setPosition(0, 40);
        leftPanel.setFillColor(PANEL_COLOR);

        // Panel derecho (propiedades)
        rightPanel.setSize(sf::Vector2f(250, window.getSize().y - 80));
        rightPanel.setPosition(window.getSize().x - 250, 40);
        rightPanel.setFillColor(PANEL_COLOR);

        // Barra inferior (estado)
        bottomBar.setSize(sf::Vector2f(window.getSize().x, 40));
        bottomBar.setPosition(0, window.getSize().y - 40);
        bottomBar.setFillColor(DARKER_PANEL_COLOR);

        // Área de trabajo
        updateWorkArea();
    }

    void createToolButtons()
    {
        float buttonY = 50;

        // Botón Play/Stop
        toolButtons.push_back(std::make_unique<Button>(
            sf::Vector2f(10, buttonY),
            sf::Vector2f(180, 30),
            "Play",
            [this]()
            { togglePlayMode(); }));
        buttonY += 40;

        // Botón Select
        toolButtons.push_back(std::make_unique<Button>(
            sf::Vector2f(10, buttonY),
            sf::Vector2f(180, 30),
            "Select",
            [this]()
            { setTool(EditorTool::Select); }));
        buttonY += 40;

        // Botón Sprite
        toolButtons.push_back(std::make_unique<Button>(
            sf::Vector2f(10, buttonY),
            sf::Vector2f(180, 30),
            "Add Sprite",
            [this]()
            { setTool(EditorTool::AddSprite); }));
        buttonY += 40;
    }

    void drawPanels()
    {
        window.draw(topBar);
        window.draw(leftPanel);
        window.draw(rightPanel);
        window.draw(bottomBar);
        window.draw(workArea);
    }

    void drawToolButtons()
    {
        for (auto &button : toolButtons)
        {
            button->draw(window);
        }
    }

    void drawStatusBar()
    {
        sf::Text statusText;
        statusText.setFont(font);
        statusText.setCharacterSize(12);
        statusText.setFillColor(sf::Color::White);
        statusText.setString(
            "Zoom: " + std::to_string(static_cast<int>(zoom * 100)) + "% | " +
            "Position: " + std::to_string(static_cast<int>(panOffset.x)) + ", " +
            std::to_string(static_cast<int>(panOffset.y)));
        statusText.setPosition(10, window.getSize().y - 30);
        window.draw(statusText);
    }

    void drawGrid()
    {
        if (!isPlaying)
        {
            const float GRID_SIZE = 32.0f * zoom;
            const sf::Vector2f workAreaPos = workArea.getPosition();
            const sf::Vector2f workAreaSize = workArea.getSize();

            // Líneas verticales
            for (float x = workAreaPos.x; x <= workAreaPos.x + workAreaSize.x; x += GRID_SIZE)
            {
                sf::RectangleShape line(sf::Vector2f(1, workAreaSize.y));
                line.setPosition(x, workAreaPos.y);
                line.setFillColor(sf::Color(100, 100, 100, 50));
                window.draw(line);
            }

            // Líneas horizontales
            for (float y = workAreaPos.y; y <= workAreaPos.y + workAreaSize.y; y += GRID_SIZE)
            {
                sf::RectangleShape line(sf::Vector2f(workAreaSize.x, 1));
                line.setPosition(workAreaPos.x, y);
                line.setFillColor(sf::Color(100, 100, 100, 50));
                window.draw(line);
            }
        }
    }

    void updateWorkArea()
    {
        float x = leftPanel.getSize().x;
        float y = topBar.getSize().y;
        float width = window.getSize().x - leftPanel.getSize().x - rightPanel.getSize().x;
        float height = window.getSize().y - topBar.getSize().y - bottomBar.getSize().y;

        workArea.setPosition(x, y);
        workArea.setSize(sf::Vector2f(width, height));
        workArea.setFillColor(WORK_AREA_COLOR);
    }

    void handlePanning(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseMoved)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
            {
                static sf::Vector2i lastMousePos = sf::Mouse::getPosition(window);
                sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                sf::Vector2i delta = currentMousePos - lastMousePos;

                panOffset += sf::Vector2f(delta);
                lastMousePos = currentMousePos;
            }
        }
    }

    void handleZoom(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.delta > 0)
                zoom *= 1.1f;
            else
                zoom *= 0.9f;

            zoom = std::clamp(zoom, 0.1f, 5.0f);
        }
    }

    void togglePlayMode()
    {
        isPlaying = !isPlaying;
        toolButtons[0]->setText(isPlaying ? "Stop" : "Play");
    }

    void setTool(EditorTool tool)
    {
        // Implementar cambio de herramienta
    }
};