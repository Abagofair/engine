#pragma once

#include <cstdint>

#include "External/include/entt/entt.hpp"
#include "External/include/glm/glm.hpp"

namespace Engine::Global::Components
{
    struct TransformComponent
    {
        glm::vec2 position;
        glm::vec2 scale;
        float rotation;
        
        bool recalculateTransform;
        glm::mat4 transform;

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::vec2& position, 
            const glm::vec2& scale, 
            const float& rotation)
            : position(position), scale(scale), rotation(rotation), recalculateTransform(false)
            {}
    };

    template<typename T>
    struct BaseComponent
    {
        T entityType;

        BaseComponent() = default;
        BaseComponent(const BaseComponent&) = default;
        BaseComponent(T entityType)
            : entityType(entityType)
            {}
    };

    struct EntityStateComponent
    {
        bool active;

        EntityStateComponent() = default;
        EntityStateComponent(const EntityStateComponent&) = default;
        EntityStateComponent(bool active)
            : active(active)
            {}
    };
};