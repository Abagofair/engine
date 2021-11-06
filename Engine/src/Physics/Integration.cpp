#include "Physics/Integration.hpp"

namespace Engine::Physics
{
    void Integrate(entt::registry &registry, Global::Time::Time time)
    {
        auto integrateableView = registry.view<
                Physics::Components::VelocityComponent,
                Global::Components::TransformComponent>();

        for (auto entity : integrateableView)
        {
            auto& velocity = integrateableView.get<Physics::Components::VelocityComponent>(entity);
            auto& sprite = integrateableView.get<Global::Components::TransformComponent>(entity);

            glm::vec2 integratedVelocity = velocity.velocity * time.SecElapsedFrame;

            glm::vec2 copy = glm::abs(velocity.velocity);
            if (copy.y != 0.0f)
            {
                sprite.position += integratedVelocity;

                sprite.recalculateTransform = true;
            }
            else
            {
                sprite.recalculateTransform = false;
            }
        }
    }
};