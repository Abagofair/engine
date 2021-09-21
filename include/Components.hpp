#pragma once

#include <cstdint>
#include <entt/entt.hpp>
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
        glm::vec2 position;
        glm::vec2 scale;
        float rotation;
        bool recalculateTransform;

        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;
        SpriteComponent(const glm::vec2& position, 
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

    enum EntityType 
    {
        Player,
        LeftPaddle,
        RightPaddle,
        Block,
        Ball        
    };

    struct BaseComponent
    {
        EntityType entityType;

        BaseComponent() = default;
        BaseComponent(const BaseComponent&) = default;
        BaseComponent(EntityType entityType)
            : entityType(entityType)
            {}
    };

    enum PaddleState
    {
        UP,
        DOWN,
        STOP
    };

    struct LeftPaddleComponent
    {
        glm::vec2 maxAcceleration;
        glm::vec2 acceleration;
        glm::vec2 velocityCeiling;
        PaddleState state;
        entt::entity attached;

        LeftPaddleComponent() = default;
        LeftPaddleComponent(const LeftPaddleComponent&) = default;
        LeftPaddleComponent(const glm::vec2& acceleration, const glm::vec2& velocityCeiling,
            entt::entity attached)
            : acceleration(acceleration), velocityCeiling(velocityCeiling), attached(attached)
            {}
    };

    struct RightPaddleComponent : public LeftPaddleComponent
    {
        RightPaddleComponent() = default;
        RightPaddleComponent(const RightPaddleComponent&) = default;
        RightPaddleComponent(const glm::vec2& acceleration, const glm::vec2& velocityCeiling,
            entt::entity attached)
            : LeftPaddleComponent(acceleration, velocityCeiling, attached)
            {}
    };

    struct BoundingBoxComponent {
        float width;
        float height;

        BoundingBoxComponent() = default;
        BoundingBoxComponent(const BoundingBoxComponent&) = default;
        BoundingBoxComponent(float width, float height)
            : width(width), height(height)
            {}
    };

    enum BallState {
        Active,
        Launch,
        Attached
    };

    struct BallComponent {
        BallState ballState;

        BallComponent() = default;
        BallComponent(const BallComponent&) = default;
        BallComponent(BallState ballState)
            : ballState(ballState)
            {}
    };

    struct PositionComponent {
        glm::vec2 position;

        PositionComponent() = default;
        PositionComponent(const PositionComponent&) = default;
        PositionComponent(glm::vec2& position)
            : position(position)
            {}
    };
};