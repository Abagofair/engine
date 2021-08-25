#include <Systems/IntegrationSystem.hpp>

IntegrationSystem::IntegrationSystem(
    entt::registry& registry
) : registry(registry)
{}

void IntegrationSystem::Integrate(InternalTime::Time time)
{
    auto playerView = registry.view<
        Components::VelocityComponent,
        Components::SpriteComponent>();

    for (auto entity : playerView)
    {
        auto& velocity = playerView.get<Components::VelocityComponent>(entity);
        auto& sprite = playerView.get<Components::SpriteComponent>(entity);

        velocity.velocity.x = velocity.velocity.x * time.SecElapsedFrame;
        
        glm::uvec2 prevPosition = sprite.position;
        sprite.position += velocity.velocity;

        if (prevPosition != sprite.position)
            sprite.recalculateTransform = true;
        else
            sprite.recalculateTransform = false;
    }
}