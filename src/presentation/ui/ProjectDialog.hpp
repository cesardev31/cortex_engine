#pragma once
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include <memory>
#include <vector>
#include "../../infrastructure/storage/ProjectRepository.hpp"
#include "CreateProjectDialog.hpp"
#include "../../core/EngineState.hpp"
#include "../../domain/entities/Project.hpp"
#include <filesystem>
#include <iostream>

class ProjectDialog
{
private:
    sf::RenderWindow &window;
    sf::Font font;
    sf::RectangleShape background;
    sf::Text titleText;
    sf::Text recentProjectsText;
    std::unique_ptr<Button> createProjectButton;
    std::unique_ptr<Button> openProjectButton;
    std::unique_ptr<Button> exitButton;

    struct RecentProject
    {
        std::string name;
        std::string path;
        sf::Text nameText;
        sf::RectangleShape highlight;
        bool isHovered;
    };

    std::vector<RecentProject> recentProjects;
    CreateProjectDialog createProjectDialog;
    bool isModalOpen = false;

public:
    ProjectDialog(sf::RenderWindow &win)
        : window(win)
    {
        // Cargar fuente
        if (!font.loadFromFile("resources/fonts/Roboto/Roboto-Bold.ttf"))
        {
            throw std::runtime_error("No se pudo cargar la fuente");
        }

        // Fondo con gradiente moderno
        background.setSize(sf::Vector2f(800, 600));
        background.setFillColor(sf::Color(28, 32, 38)); // Color base más oscuro

        // Título con estilo moderno
        titleText.setFont(font);
        titleText.setString("CORTEX ENGINE");
        titleText.setCharacterSize(36);
        titleText.setFillColor(sf::Color(240, 240, 240));
        titleText.setPosition(50, 40);
        titleText.setStyle(sf::Text::Bold);

        // Botones principales con nuevo estilo
        createProjectButton = std::make_unique<Button>(
            sf::Vector2f(50, 120),
            sf::Vector2f(220, 50),
            "NUEVO PROYECTO",
            [this]()
            { onCreateProject(); },
            sf::Color(76, 175, 80) // Verde material
        );

        openProjectButton = std::make_unique<Button>(
            sf::Vector2f(290, 120),
            sf::Vector2f(220, 50),
            "ABRIR PROYECTO",
            [this]()
            { onOpenProject(); },
            sf::Color(33, 150, 243) // Azul material
        );

        // Sección de proyectos recientes
        recentProjectsText.setFont(font);
        recentProjectsText.setString("PROYECTOS RECIENTES");
        recentProjectsText.setCharacterSize(20);
        recentProjectsText.setFillColor(sf::Color(180, 180, 180));
        recentProjectsText.setPosition(50, 200);
        recentProjectsText.setStyle(sf::Text::Bold);

        // Cargar proyectos desde SQLite
        loadRecentProjects();

        // Botón de salida en la parte inferior
        exitButton = std::make_unique<Button>(
            sf::Vector2f(50, 520), // Posición en la parte inferior
            sf::Vector2f(120, 40),
            "SALIR",
            [this]()
            { onExit(); },
            sf::Color(220, 53, 69) // Color rojo para indicar acción destructiva
        );
    }

    void handleEvent(const sf::Event &event, const sf::RenderWindow &window)
    {
        if (createProjectDialog.isVisible())
        {
            createProjectDialog.handleEvent(event, window);
            return;
        }

        // Procesar eventos normales solo si no hay modal abierto
        createProjectButton->handleEvent(event, window);
        openProjectButton->handleEvent(event, window);

        // Manejar eventos de proyectos recientes
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x),
                               static_cast<float>(mousePos.y));

        for (auto &project : recentProjects)
        {
            bool wasHovered = project.isHovered;
            project.isHovered = project.highlight.getGlobalBounds().contains(mousePosF);

            if (project.isHovered && !wasHovered)
            {
                project.highlight.setFillColor(sf::Color(60, 64, 72));
            }
            else if (!project.isHovered && wasHovered)
            {
                project.highlight.setFillColor(sf::Color(50, 54, 62));
            }

            if (project.isHovered && event.type == sf::Event::MouseButtonPressed)
            {
                openRecentProject(project.path);
            }
        }

        if (!createProjectDialog.isVisible())
        {
            exitButton->handleEvent(event, window);
        }
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(background);
        window.draw(titleText);

        // Cambiar la condición para usar isVisible del diálogo
        if (!createProjectDialog.isVisible())
        {
            createProjectButton->draw(window);
            openProjectButton->draw(window);
            window.draw(recentProjectsText);

            // Dibujar proyectos recientes
            if (recentProjects.empty())
            {
                sf::Text noProjectsText;
                noProjectsText.setFont(font);
                noProjectsText.setString("No hay proyectos recientes");
                noProjectsText.setCharacterSize(20);
                noProjectsText.setFillColor(sf::Color(120, 120, 120));
                noProjectsText.setPosition(50, 230);
                window.draw(noProjectsText);
            }
            else
            {
                for (const auto &project : recentProjects)
                {
                    window.draw(project.highlight);
                    window.draw(project.nameText);
                }
            }

            exitButton->draw(window);
        }

        createProjectDialog.draw(window);
    }

private:
    void loadRecentProjects()
    {
        Infrastructure::ProjectRepository repo;
        auto projects = repo.getRecentProjects(5); // Cargar los 5 más recientes

        for (const auto &project : projects)
        {
            addRecentProject(project.getName(), project.getPath().string());
        }
    }

    void addRecentProject(const std::string &name, const std::string &path)
    {
        RecentProject project;
        project.name = name;
        project.path = path;
        project.isHovered = false;

        // Configurar el texto del proyecto
        project.nameText.setFont(font);
        project.nameText.setString(name);
        project.nameText.setCharacterSize(20);
        project.nameText.setFillColor(sf::Color::White);
        project.nameText.setPosition(60, 230 + recentProjects.size() * 40);

        // Configurar el highlight del proyecto
        project.highlight.setSize(sf::Vector2f(700, 35));
        project.highlight.setPosition(50, 225 + recentProjects.size() * 40);
        project.highlight.setFillColor(sf::Color(50, 54, 62));

        recentProjects.push_back(project);
    }

    void onCreateProject()
    {
        createProjectDialog.setOnProjectCreatedCallback([this](const Domain::ProjectInfo &project)
                                                        {
            // Ocultar el diálogo de creación
            createProjectDialog.hide();
            
            // Iniciar el motor con el nuevo proyecto
            try {
                EngineState engineState(window, project);
                engineState.run();
            } catch (const std::exception& e) {
                std::cerr << "Error al iniciar el motor: " << e.what() << std::endl;
                // TODO: Mostrar mensaje de error al usuario
            } });

        createProjectDialog.show();
    }

    void onOpenProject()
    {
        std::cout << "Abrir proyecto existente" << std::endl;
        // TODO: Implementar diálogo de apertura
    }

    void openRecentProject(const std::string &path)
    {
        try
        {
            Domain::ProjectInfo project(
                std::filesystem::path(path).filename().string(),
                path);

            // Ocultar el diálogo de proyectos
            isModalOpen = false;

            // Iniciar el motor con el proyecto seleccionado
            EngineState engineState(window, project);
            engineState.run();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error al abrir el proyecto: " << e.what() << std::endl;
            // TODO: Mostrar mensaje de error al usuario
        }
    }

    // Agregar método para cerrar el modal
    void closeModal()
    {
        isModalOpen = false;
    }

    void onExit()
    {
        // Puedes agregar aquí lógica adicional antes de cerrar
        std::cout << "Cerrando aplicación..." << std::endl;
        std::exit(0); // O enviar un evento de cierre a la ventana
    }
};
