#pragma once
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include <memory>
#include <vector>
#include "../../infrastructure/storage/ProjectRepository.hpp"

class ProjectDialog
{
private:
    sf::Font font;
    sf::RectangleShape background;
    sf::Text titleText;
    sf::Text recentProjectsText;
    std::unique_ptr<Button> createProjectButton;
    std::unique_ptr<Button> openProjectButton;

    struct RecentProject
    {
        std::string name;
        std::string path;
        sf::Text nameText;
        sf::RectangleShape highlight;
        bool isHovered;
    };

    std::vector<RecentProject> recentProjects;

public:
    ProjectDialog()
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
    }

    void handleEvent(const sf::Event &event, const sf::RenderWindow &window)
    {
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
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(background);
        window.draw(titleText);
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
        std::cout << "Crear nuevo proyecto" << std::endl;
        // TODO: Implementar diálogo de creación
    }

    void onOpenProject()
    {
        std::cout << "Abrir proyecto existente" << std::endl;
        // TODO: Implementar diálogo de apertura
    }

    void openRecentProject(const std::string &path)
    {
        std::cout << "Abriendo proyecto reciente: " << path << std::endl;
        // TODO: Implementar apertura de proyecto
    }
};