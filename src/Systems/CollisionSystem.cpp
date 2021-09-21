#include <Systems/CollisionSystem.hpp>

CollisionSystem::CollisionSystem(
    entt::registry& registry, Window& window
) : _registry(registry), _window(window)
{
    _entityCollisionHandlers = std::unordered_map<entt::entity,
        std::unordered_map<Components::EntityType, std::function<void(CollisionInfo)>>>();
}

void CollisionSystem::HandleViewport()
{
    auto velocityView = _registry.view<
        Components::BaseComponent,
        Components::VelocityComponent,
        Components::SpriteComponent,
        Components::BoundingBoxComponent>();

    auto boundingBoxView = _registry.view<
        Components::BaseComponent,
        Components::BoundingBoxComponent,
        Components::SpriteComponent>();

    glm::uvec2 windowDimensions = _window.WindowDimensions();

    for (auto aEntity : velocityView)
    {
        auto& velocity = velocityView.get<Components::VelocityComponent>(aEntity);
        auto& sprite = velocityView.get<Components::SpriteComponent>(aEntity);
        auto& boundingBox = velocityView.get<Components::BoundingBoxComponent>(aEntity);
        auto& aBase = velocityView.get<Components::BaseComponent>(aEntity);

        if (sprite.position.y < 0.0f)
        {
            velocity.velocity.y *= -1;
            sprite.position.y = 0.0f;
        }
        else if (sprite.position.y > (windowDimensions.y - boundingBox.height))
        {
            velocity.velocity.y *= -1;
            sprite.position.y = windowDimensions.y - boundingBox.height;
        }

        float aMinX = sprite.position.x;
        float aMinY = sprite.position.y;
        float aMaxX = boundingBox.width + aMinX;
        float aMaxY = boundingBox.height + aMinY;

        for (auto bEntity : boundingBoxView)
        {
            auto& boundingBoxComponent = boundingBoxView.get<Components::BoundingBoxComponent>(bEntity);
            auto& positionComponent = boundingBoxView.get<Components::SpriteComponent>(bEntity);
            auto& bBase = velocityView.get<Components::BaseComponent>(aEntity);

            float bMinX = positionComponent.position.x;
            float bMinY = positionComponent.position.y;
            float bMaxX = boundingBoxComponent.width + bMinX;
            float bMaxY = boundingBoxComponent.height + bMinY;

            if (aEntity == bEntity)
                continue;

            if (velocity.velocity.x == 0) continue; //todo: if player hack
            
            if (aMinX < bMaxX && aMaxX > bMinX && aMinY < bMaxY && aMaxY > bMinY)
            {
                if (aMinX > bMinX)
                    sprite.position.x = bMaxX + 1.0f;
                else if (aMinX <= bMinX)
                    sprite.position.x = positionComponent.position.x - boundingBox.width;

                auto entityCollisionHandlers = _entityCollisionHandlers.find(aEntity);
                if (entityCollisionHandlers == _entityCollisionHandlers.end())
                {
                    continue;
                }

                auto collisionHandler = entityCollisionHandlers->second.find(bBase.entityType);
                if (collisionHandler != entityCollisionHandlers->second.end())
                {
                    CollisionInfo collisionInfo;
                    collisionInfo.collisionEntity = bEntity;
                    collisionHandler->second(collisionInfo);
                }
            }
        }
    }
}

void CollisionSystem::AddCollisionHandler(entt::entity entity, Components::EntityType entityType, 
        std::function<void(CollisionInfo)> handler)
{
    _entityCollisionHandlers[entity][entityType] = handler;
}