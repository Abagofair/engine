#pragma once

#include "External/include/entt/entt.hpp"
#include "External/include/glm/glm.hpp"

namespace Game::Components
{
    enum PaddleState
    {
        Up,
        Down,
        Stop,
        Braking,
        Moving
    };

    enum BallState 
    {
        Active,
        Launch,
        Attached
    };

    struct LeftPaddleComponent
    {
        glm::vec2 maxAcceleration;
        glm::vec2 acceleration;
        glm::vec2 velocityCeiling;
        float brakeMagnitude;
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
};