#pragma once

#include <cstdint>

#include <External/entt/entt.hpp>
#include <External/glm/glm.hpp>

#include <Engine/Global/Generated/Types.hpp>

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

    struct BaseComponent
    {
        Generated::EntityType entityType;

        BaseComponent() = default;
        BaseComponent(const BaseComponent&) = default;
        BaseComponent(Generated::EntityType entityType)
            : entityType(entityType)
            {}
    };
};