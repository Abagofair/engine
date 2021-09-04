#include <Systems/CollisionSystem.hpp>

CollisionSystem::CollisionSystem(
    entt::registry& registry, Window& window
) : _registry(registry), _window(window)
{}

void CollisionSystem::ResolveVelocities()
{
    auto velocityView = _registry.view<
        Components::VelocityComponent,
        Components::SpriteComponent, 
        Components::BoundingBoxComponent>();

    glm::uvec2 windowDimensions = _window.WindowDimensions();

    for (auto entity : velocityView)
    {
        auto& velocity = velocityView.get<Components::VelocityComponent>(entity);
        auto& sprite = velocityView.get<Components::SpriteComponent>(entity);
        auto& boundingBox = velocityView.get<Components::BoundingBoxComponent>(entity);

        if (sprite.position.y < boundingBox.height)
        {
            velocity.velocity.y *= -1;
            sprite.position.y = boundingBox.height;
        }
        else if (sprite.position.y > (windowDimensions.y - boundingBox.height))
        {
            velocity.velocity.y *= -1;
            sprite.position.y = windowDimensions.y - boundingBox.height;
        }
    }
}

