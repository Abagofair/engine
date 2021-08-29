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
        
        velocity.velocity *= time.SecElapsedFrame;

        glm::vec2 copy = glm::abs(velocity.velocity);
       /* if (copy.y > 0.0f)
        {
            sprite.position = velocity.velocity;
            sprite.recalculateTransform = true;
        }
        else
        {
            //todo: this ruins the deceleration when not applying axis input
            sprite.position = glm::vec2(0.0f, 0.0f);
            sprite.recalculateTransform = false;
        }*/
        sprite.position = velocity.velocity;
        sprite.recalculateTransform = true;
    }
}