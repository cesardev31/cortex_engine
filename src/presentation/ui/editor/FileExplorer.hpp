#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>

class FileExplorer
{
private:
    sf::RenderWindow &window;
    sf::Font &font;
    sf::RectangleShape background;
    std::vector<std::filesystem::path> currentFiles;
    float scrollOffset = 0.0f;

    const sf::Color BG_COLOR{30, 30, 30};
    const sf::Color ITEM_HOVER_COLOR{45, 45, 48};
    const sf::Color TEXT_COLOR{200, 200, 200};

public:
    FileExplorer(sf::RenderWindow &win, sf::Font &f)
        : window(win), font(f)
    {
        background.setSize(sf::Vector2f(200, window.getSize().y - 65));
        background.setPosition(0, 40);
        background.setFillColor(BG_COLOR);
        refreshFileList();
    }

    void refreshFileList()
    {
        currentFiles.clear();
        // TODO: Implementar lectura de archivos del proyecto
    }

    void draw()
    {
        window.draw(background);

        sf::Text title;
        title.setFont(font);
        title.setString("Explorador");
        title.setCharacterSize(14);
        title.setFillColor(TEXT_COLOR);
        title.setPosition(10, 45);
        window.draw(title);

        float y = 70;
        for (const auto &file : currentFiles)
        {
            sf::Text fileText;
            fileText.setFont(font);
            fileText.setString(file.filename().string());
            fileText.setCharacterSize(12);
            fileText.setFillColor(TEXT_COLOR);
            fileText.setPosition(20, y);
            window.draw(fileText);
            y += 20;
        }
    }

    void handleEvent(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            handleClick(event.mouseButton);
        }
        else if (event.type == sf::Event::MouseWheelScrolled)
        {
            handleScroll(event.mouseWheelScroll);
        }
    }

private:
    void handleClick(const sf::Event::MouseButtonEvent &mouseButton)
    {
        // TODO: Implementar lógica de click
    }

    void handleScroll(const sf::Event::MouseWheelScrollEvent &scroll)
    {
        if (scroll.delta > 0)
        {
            scrollOffset = std::max(0.0f, scrollOffset - 20.0f);
        }
        else
        {
            scrollOffset += 20.0f;
        }
    }
};