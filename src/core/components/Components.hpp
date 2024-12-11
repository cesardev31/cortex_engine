#pragma once
#include <SFML/System/Vector2.hpp>

namespace Core
{
    struct Transform
    {
        sf::Vector2f position;
        float rotation;
        sf::Vector2f scale;

        Transform(const sf::Vector2f &pos = sf::Vector2f(0, 0),
                  float rot = 0.0f,
                  const sf::Vector2f &scl = sf::Vector2f(1, 1))
            : position(pos), rotation(rot), scale(scl) {}
    };

    struct Sprite
    {
        std::string textureId;
        float width;
        float height;

        Sprite(const std::string &id = "", float w = 0, float h = 0)
            : textureId(id), width(w), height(h) {}
    };

    struct Physics
    {
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
        float mass;

        Physics(const sf::Vector2f &vel = sf::Vector2f(0, 0),
                const sf::Vector2f &acc = sf::Vector2f(0, 0),
                float m = 1.0f)
            : velocity(vel), acceleration(acc), mass(m) {}
    };
}
