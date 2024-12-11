#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <any>

namespace Core
{
    using EntityId = std::uint64_t;

    class World
    {
    private:
        struct Entity
        {
            EntityId id;
            std::unordered_map<std::type_index, std::any> components;
        };

        std::unordered_map<EntityId, Entity> entities;
        EntityId nextEntityId = 0;

    public:
        EntityId createEntity()
        {
            EntityId entityId = nextEntityId++;
            entities[entityId] = Entity{entityId};
            return entityId;
        }

        template <typename T>
        void addComponent(EntityId entityId, T component)
        {
            if (auto it = entities.find(entityId); it != entities.end())
            {
                it->second.components[std::type_index(typeid(T))] = component;
            }
        }

        template <typename T>
        T *getComponent(EntityId entityId)
        {
            if (auto it = entities.find(entityId); it != entities.end())
            {
                auto &components = it->second.components;
                auto componentIt = components.find(std::type_index(typeid(T)));
                if (componentIt != components.end())
                {
                    return std::any_cast<T>(&componentIt->second);
                }
            }
            return nullptr;
        }
    };
}
