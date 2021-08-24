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
            : position(position), scale(scale), rotation(rotation), recalculateTransform(true)
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

    struct PlayerComponent //PlayerInputComponent?
    {
        //state variables

        //MoveUp action ?

        //MoveDown action ?
        //LaunchBall action ?

        PlayerComponent() = default;
        PlayerComponent(const PlayerComponent&) = default;
        /*PlayerComponent(const glm::mat4& transform)
            : transform(transform)
            {}*/


        void MoveUp()
        {
            
        }
    };
};