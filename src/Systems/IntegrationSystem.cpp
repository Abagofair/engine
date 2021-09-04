#include <Systems/IntegrationSystem.hpp>

IntegrationSystem::IntegrationSystem(
    entt::registry& registry
) : registry(registry)
{}

void IntegrationSystem::Integrate(InternalTime::Time time)
{
    auto integrateableView = registry.view<
        Components::VelocityComponent,
        Components::SpriteComponent>();

    for (auto entity : integrateableView)
    {
        auto& velocity = integrateableView.get<Components::VelocityComponent>(entity);
        auto& sprite = integrateableView.get<Components::SpriteComponent>(entity);

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