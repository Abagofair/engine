#pragma once

#include "External/include/entt/entt.hpp"
#include "External/include/glm/glm.hpp"

namespace Game::Components
{
    enum class PaddleState
    {
        Up,
        Down,
        Stop,
        Braking,
        Moving
    };

    enum class BallState
    {
        Active,
        Launch,
        Attached
    };

    enum class BlockState
    {
        Live,
        Dead
    };

    struct LeftPaddleComponent
    {
        glm::vec2 maxAcceleration;
        glm::vec2 acceleration;
        glm::vec2 velocityCeiling;
        float brakeForce;
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

    struct BallComponent {
        BallState ballState;

        BallComponent() = default;
        BallComponent(const BallComponent&) = default;
        BallComponent(BallState ballState)
            : ballState(ballState)
            {}
    };

    struct BlockComponent {
        BlockState blockState;

        BlockComponent() = default;
        BlockComponent(const BlockComponent&) = default;
        BlockComponent(BlockState blockState)
        : blockState(blockState)
                {}
    };
};