#pragma once
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include <memory>
#include <functional>
#include <filesystem>
#include "../../domain/services/ProjectManager.hpp"

class CreateProjectDialog
{
private:
    sf::RectangleShape background;
    sf::RectangleShape modal;
    sf::Font font;
    sf::Text titleText;
    sf::Text nameLabel;
    sf::Text pathLabel;

    // Campos de entrada
    sf::RectangleShape nameInput;
    sf::RectangleShape pathInput;
    sf::Text nameText;
    sf::Text pathText;
    bool isNameFocused = false;
    bool isPathFocused = false;

    std::unique_ptr<Button> createButton;
    std::unique_ptr<Button> cancelButton;
    bool m_isVisible = false;

    // Agregar nuevas variables para el cursor
    sf::RectangleShape textCursor;
    sf::Clock cursorClock;
    bool showCursor = true;

    // Agregar botón para explorar
    std::unique_ptr<Button> browseButton;

    std::function<void()> onCloseCallback;
    std::function<void(const Domain::ProjectInfo &)> onProjectCreated;

public:
    CreateProjectDialog()
    {
        if (!font.loadFromFile("resources/fonts/Roboto/Roboto-Regular.ttf"))
        {
            throw std::runtime_error("No se pudo cargar la fuente");
        }

        // Fondo semi-transparente
        background.setSize(sf::Vector2f(800, 600));
        background.setFillColor(sf::Color(0, 0, 0, 180));

        // Ventana modal
        modal.setSize(sf::Vector2f(500, 300));
        modal.setFillColor(sf::Color(45, 45, 48));
        modal.setOutlineColor(sf::Color(60, 60, 65));
        modal.setOutlineThickness(1.0f);

        // Título
        titleText.setFont(font);
        titleText.setString("Crear Nuevo Proyecto");
        titleText.setCharacterSize(24);
        titleText.setFillColor(sf::Color::White);

        // Labels
        nameLabel.setFont(font);
        nameLabel.setString("Nombre del Proyecto:");
        nameLabel.setCharacterSize(16);
        nameLabel.setFillColor(sf::Color::White);

        pathLabel.setFont(font);
        pathLabel.setString(L"Ubicación:");
        pathLabel.setCharacterSize(16);
        pathLabel.setFillColor(sf::Color::White);

        // Campos de entrada
        nameInput.setSize(sf::Vector2f(400, 30));
        nameInput.setFillColor(sf::Color(60, 60, 65));
        nameInput.setOutlineColor(sf::Color(70, 70, 75));
        nameInput.setOutlineThickness(1.0f);

        pathInput.setSize(sf::Vector2f(310, 30));
        pathInput.setFillColor(sf::Color(60, 60, 65));
        pathInput.setOutlineColor(sf::Color(70, 70, 75));
        pathInput.setOutlineThickness(1.0f);

        nameText.setFont(font);
        nameText.setCharacterSize(16);
        nameText.setFillColor(sf::Color::White);

        pathText.setFont(font);
        pathText.setCharacterSize(16);
        pathText.setFillColor(sf::Color::White);

        // Botones
        createButton = std::make_unique<Button>(
            sf::Vector2f(0, 0), // Se actualizará en updatePositions()
            sf::Vector2f(120, 40),
            "Crear",
            [this]()
            { onCreateProject(); },
            sf::Color(76, 175, 80));

        cancelButton = std::make_unique<Button>(
            sf::Vector2f(0, 0), // Se actualizará en updatePositions()
            sf::Vector2f(120, 40),
            "Cancelar",
            [this]()
            { hide(); },
            sf::Color(120, 120, 120));

        // Configurar el cursor de texto
        textCursor.setSize(sf::Vector2f(2, 24));
        textCursor.setFillColor(sf::Color::White);

        // Botón de explorar
        browseButton = std::make_unique<Button>(
            sf::Vector2f(0, 0),
            sf::Vector2f(80, 30),
            "...",
            [this]()
            { openFileDialog(); },
            sf::Color(70, 70, 70));

        updatePositions();

        onCloseCallback = [this]()
        {
            m_isVisible = false;
        };
    }

    void show()
    {
        m_isVisible = true;
        nameText.setString("");
        pathText.setString("");
    }

    void hide()
    {
        m_isVisible = false;
        if (onCloseCallback)
        {
            onCloseCallback();
        }
    }

    void handleEvent(const sf::Event &event, const sf::RenderWindow &window)
    {
        if (!m_isVisible)
            return;

        if (event.type == sf::Event::TextEntered)
        {
            if (isNameFocused)
            {
                handleTextInput(nameText, event.text.unicode);
            }
            else if (isPathFocused)
            {
                handleTextInput(pathText, event.text.unicode);
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (event.type == sf::Event::MouseButtonPressed)
        {
            isNameFocused = nameInput.getGlobalBounds().contains(mousePos.x, mousePos.y);
            isPathFocused = pathInput.getGlobalBounds().contains(mousePos.x, mousePos.y);
        }

        createButton->handleEvent(event, window);
        cancelButton->handleEvent(event, window);
        browseButton->handleEvent(event, window);

        // Reiniciar el cursor cuando se escribe
        if (event.type == sf::Event::TextEntered)
        {
            showCursor = true;
            cursorClock.restart();
        }
    }

    void draw(sf::RenderWindow &window)
    {
        if (!m_isVisible)
            return;

        window.draw(background);
        window.draw(modal);
        window.draw(titleText);
        window.draw(nameLabel);
        window.draw(pathLabel);
        window.draw(nameInput);
        window.draw(pathInput);
        window.draw(nameText);
        window.draw(pathText);
        createButton->draw(window);
        cancelButton->draw(window);

        // Dibujar el cursor si está enfocado
        if ((isNameFocused || isPathFocused) && showCursor)
        {
            if (cursorClock.getElapsedTime().asMilliseconds() > 500)
            {
                showCursor = !showCursor;
                cursorClock.restart();
            }

            if (showCursor)
            {
                if (isNameFocused)
                {
                    textCursor.setPosition(
                        nameText.getPosition().x + nameText.getLocalBounds().width + 2,
                        nameText.getPosition().y);
                    window.draw(textCursor);
                }
                else if (isPathFocused)
                {
                    textCursor.setPosition(
                        pathText.getPosition().x + pathText.getLocalBounds().width + 2,
                        pathText.getPosition().y);
                    window.draw(textCursor);
                }
            }
        }

        browseButton->draw(window);
    }

    void setOnCloseCallback(std::function<void()> callback)
    {
        onCloseCallback = callback;
    }

    bool isVisible() const
    {
        return m_isVisible;
    }

    void setOnProjectCreatedCallback(std::function<void(const Domain::ProjectInfo &)> callback)
    {
        onProjectCreated = callback;
    }

private:
    void updatePositions()
    {
        // Centrar la ventana modal
        sf::Vector2f modalPos(
            (800 - modal.getSize().x) / 2,
            (600 - modal.getSize().y) / 2);
        modal.setPosition(modalPos);

        // Posicionar elementos dentro de la modal
        titleText.setPosition(
            modalPos.x + (modal.getSize().x - titleText.getLocalBounds().width) / 2,
            modalPos.y + 20);

        nameLabel.setPosition(modalPos.x + 50, modalPos.y + 80);
        nameInput.setPosition(modalPos.x + 50, modalPos.y + 110);
        nameText.setPosition(modalPos.x + 55, modalPos.y + 115);

        pathLabel.setPosition(modalPos.x + 50, modalPos.y + 150);
        pathInput.setPosition(modalPos.x + 50, modalPos.y + 180);
        pathText.setPosition(modalPos.x + 55, modalPos.y + 185);

        // Posicionar botones
        float buttonY = modalPos.y + modal.getSize().y - 60;
        createButton->setPosition(
            modalPos.x + modal.getSize().x - 290,
            buttonY);
        cancelButton->setPosition(
            modalPos.x + modal.getSize().x - 150,
            buttonY);

        // Posicionar el botón de explorar
        browseButton->setPosition(
            pathInput.getPosition().x + pathInput.getSize().x + 10,
            pathInput.getPosition().y);
    }

    void handleTextInput(sf::Text &text, uint32_t unicode)
    {
        std::string str = text.getString();
        if (unicode == 8)
        { // Backspace
            if (!str.empty())
            {
                str.pop_back();
            }
        }
        else if (unicode == 13)
        { // Enter
          // Manejar enter si es necesario
        }
        else if (unicode >= 32)
        {
            str += static_cast<char>(unicode);
        }
        text.setString(str);
    }

    void onCreateProject()
    {
        std::string name = nameText.getString();
        std::string path = pathText.getString();
        if (!name.empty() && !path.empty())
        {
            ProjectManager projectManager;
            std::filesystem::path projectPath = std::filesystem::path(path) / name;
            if (projectManager.createProject(name, projectPath))
            {
                std::cout << "Proyecto creado exitosamente" << std::endl;

                // Crear el objeto ProjectInfo y pasarlo al callback
                Domain::ProjectInfo project(name, projectPath);
                if (onProjectCreated)
                {
                    onProjectCreated(project);
                }

                hide();
            }
            else
            {
                std::cout << "Error al crear el proyecto" << std::endl;
            }
        }
    }

    void openFileDialog()
    {
#ifdef __linux__
        try
        {
            // Usar una biblioteca más moderna para diálogos nativos
            // Por ejemplo, nativefiledialog-extended (NFD)
            // O implementar un diálogo personalizado con SFML

            std::string cmd = "zenity --file-selection --directory"
                              " --title=\"Seleccionar ubicación del proyecto\""
                              " --window-icon=question"
                              " 2>/dev/null"; // Suprimir advertencias

            FILE *pipe = popen(cmd.c_str(), "r");
            if (!pipe)
            {
                throw std::runtime_error("No se pudo abrir el diálogo de selección");
            }

            std::array<char, 1024> buffer;
            std::string result;

            while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
            {
                result += buffer.data();
            }

            int status = pclose(pipe);
            if (status == 0 && !result.empty())
            {
                if (result.back() == '\n')
                {
                    result.pop_back();
                }
                pathText.setString(result);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error en el diálogo de selección: " << e.what() << std::endl;
        }
#endif
    }
};