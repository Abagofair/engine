#pragma once

namespace Engine::Physics::Components
{
    struct VelocityComponent
    {
        glm::vec2 velocity;

        VelocityComponent() = default;
        VelocityComponent(const VelocityComponent&) = default;
        VelocityComponent(const glm::vec2& velocity)
            : velocity(velocity)
            {}
    };
};