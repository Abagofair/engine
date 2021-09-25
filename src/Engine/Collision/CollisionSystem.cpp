#include <Engine/Collision/CollisionSystem.hpp>

namespace Engine::Collision
{
    CollisionSystem::CollisionSystem(
        entt::registry& registry
    ) : _registry(registry)
    {
        _entityCollisionHandlers = std::unordered_map<entt::entity,
            std::unordered_map<Engine::Global::Generated::EntityType, std::function<void(CollisionInfo)>>>();
    }

    void CollisionSystem::Handle()
    {
        auto velocityView = _registry.view<
            Engine::Global::Components::BaseComponent,
            Engine::Global::Components::TransformComponent,
            Engine::Physics::Components::VelocityComponent,
            Engine::Collision::Components::BoundingBoxComponent>();

        auto boundingBoxView = _registry.view<
            Engine::Global::Components::BaseComponent,
            Engine::Collision::Components::BoundingBoxComponent,
            Engine::Global::Components::TransformComponent>();

        for (auto aEntity : velocityView)
        {
            auto& sprite = velocityView.get<Engine::Global::Components::TransformComponent>(aEntity);
            auto& boundingBox = velocityView.get<Engine::Collision::Components::BoundingBoxComponent>(aEntity);
            auto& aBase = velocityView.get<Engine::Global::Components::BaseComponent>(aEntity);

            float aMinX = sprite.position.x;
            float aMinY = sprite.position.y;
            float aMaxX = boundingBox.width + aMinX;
            float aMaxY = boundingBox.height + aMinY;

            for (auto bEntity : boundingBoxView)
            {
                auto& boundingBoxComponent = boundingBoxView.get<Engine::Collision::Components::BoundingBoxComponent>(bEntity);
                auto& positionComponent = boundingBoxView.get<Engine::Global::Components::TransformComponent>(bEntity);
                auto& bBase = boundingBoxView.get<Engine::Global::Components::BaseComponent>(bEntity);

                float bMinX = positionComponent.position.x;
                float bMinY = positionComponent.position.y;
                float bMaxX = boundingBoxComponent.width + bMinX;
                float bMaxY = boundingBoxComponent.height + bMinY;

                if (aEntity == bEntity)
                    continue;

                if (!boundingBoxComponent.contains && aMinX < bMaxX && aMaxX > bMinX && aMinY < bMaxY && aMaxY > bMinY)
                {
                    auto entityCollisionHandlers = _entityCollisionHandlers.find(aEntity);
                    if (entityCollisionHandlers == _entityCollisionHandlers.end())
                    {
                        continue;
                    }

                    auto collisionHandler = entityCollisionHandlers->second.find(bBase.entityType);
                    if (collisionHandler != entityCollisionHandlers->second.end())
                    {
                        CollisionInfo collisionInfo;
                        collisionInfo.target = bEntity;
                        collisionInfo.source = aEntity;
                        collisionHandler->second(collisionInfo);
                    }
                }
                else if (boundingBoxComponent.contains && bMaxX > aMinX && bMaxY > aMinY && bMaxX > aMinX && bMaxY > aMinY)
                {
                    auto entityCollisionHandlers = _entityCollisionHandlers.find(aEntity);
                    if (entityCollisionHandlers == _entityCollisionHandlers.end())
                    {
                        continue;
                    }

                    auto collisionHandler = entityCollisionHandlers->second.find(bBase.entityType);
                    if (collisionHandler != entityCollisionHandlers->second.end())
                    {
                        CollisionInfo collisionInfo;
                        collisionInfo.target = bEntity;
                        collisionInfo.source = aEntity;
                        collisionHandler->second(collisionInfo);
                    }
                }
            }
        }
    }

    void CollisionSystem::AddCollisionHandler(
        entt::entity entity,
        Engine::Global::Generated::EntityType entityType,
        std::function<void(CollisionInfo)> handler)
    {
        _entityCollisionHandlers[entity][entityType] = handler;
    }
};