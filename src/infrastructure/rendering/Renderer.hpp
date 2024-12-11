#pragma once
#include <SFML/Graphics.hpp>
#include "../../core/components/Components.hpp"

namespace Infrastructure
{
    class Renderer
    {
    public:
        virtual ~Renderer() = default;
        virtual void clear(const sf::Color &color) = 0;
        virtual void drawSprite(const Core::Sprite &sprite, const Core::Transform &transform) = 0;
        virtual void drawText(const std::string &text, const sf::Vector2f &position) = 0;
        virtual void present() = 0;
    };

    class SFMLRenderer : public Renderer
    {
    private:
        sf::RenderWindow &window;

    public:
        explicit SFMLRenderer(sf::RenderWindow &win) : window(win) {}

        void clear(const sf::Color &color) override
        {
            window.clear(color);
        }

        void drawSprite(const Core::Sprite &sprite, const Core::Transform &transform) override
        {
            // Implementar dibujo de sprites
        }

        void drawText(const std::string &text, const sf::Vector2f &position) override
        {
            // Implementar dibujo de texto
        }

        void present() override
        {
            window.display();
        }
    };
}
