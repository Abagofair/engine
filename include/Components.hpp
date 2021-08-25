#pragma once

#include <cstdint>

#include <glm/glm.hpp>

namespace Components
{
    struct Texture2DComponent
    {
        uint32_t textureId;

        Texture2DComponent() = default;
        Texture2DComponent(const Texture2DComponent&) = default;
        Texture2DComponent(const uint16_t& textureId)
            : textureId(textureId) 
            {}
    };

    struct SpriteComponent
    {
        glm::uvec2 position;
        glm::vec2 scale;
        float rotation;
        bool recalculateTransform;

        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;
        SpriteComponent(const glm::uvec2& position, 
            const glm::vec2& scale, 
            const float& rotation)
            : position(position), scale(scale), rotation(rotation), recalculateTransform(false)
            {}
    };

    struct VelocityComponent
    {
        glm::vec2 velocity;

        VelocityComponent() = default;
        VelocityComponent(const VelocityComponent&) = default;
        VelocityComponent(const glm::vec2& transform)
            : velocity(transform)
            {}
    };

    struct TransformComponent
    {
        glm::mat4 transform;

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::mat4& transform)
            : transform(transform)
            {}
    };

    struct PaddleComponent
    {
        float speed;

        PaddleComponent() = default;
        PaddleComponent(const PaddleComponent&) = default;
        PaddleComponent(float speed)
            : speed(speed)
            {}
    };
};