#pragma once

#include <unordered_map>

#include <External/entt/entt.hpp>
#include <External/glm/glm.hpp>

#include <Engine/Global/Components.hpp>
#include <Engine/Physics/PhysicsComponents.hpp>
#include <Engine/Collision/CollisionComponents.hpp>

#include <iostream>

namespace Engine::Collision
{
    struct CollisionInfo
    {
        entt::entity source;
        entt::entity target;
    };

    template<typename T = int>
    class CollisionSystem
    {
    public:
        CollisionSystem(
            entt::registry& registry)
            : _registry(registry)
        {
            _entityCollisionCallbacks = std::unordered_map<entt::entity, std::unordered_map<T, std::function<void(CollisionInfo)>>>();
        }

        void BroadPhase()
        {
            auto velocityView = _registry.view<
                Global::Components::BaseComponent<T>,
                Global::Components::TransformComponent,
                Physics::Components::VelocityComponent,
                Collision::Components::BoundingBoxComponent>();

            auto boundingBoxView = _registry.view<
                Global::Components::BaseComponent<T>,
                Collision::Components::BoundingBoxComponent,
                Global::Components::TransformComponent>();

            for (auto velocityEntity : velocityView)
            {
                auto& velocityTransform = velocityView.template get<Global::Components::TransformComponent>(velocityEntity);
                auto& velocityBoundingBox = velocityView.template get<Collision::Components::BoundingBoxComponent>(velocityEntity);

                for (auto targetEntity : boundingBoxView)
                {
                    auto& targetBoundingBox = boundingBoxView.template get<Collision::Components::BoundingBoxComponent>(targetEntity);
                    auto& targetTransform = boundingBoxView.template get<Global::Components::TransformComponent>(targetEntity);
                    auto& targetBase = boundingBoxView.template get<Global::Components::BaseComponent<T>>(targetEntity);

                    if (velocityEntity == targetEntity)
                        continue;

                    if (!targetBoundingBox.contains && TestAABB(velocityBoundingBox, velocityTransform, targetBoundingBox, targetTransform))
                    {
                        CollisionCallback(velocityEntity, targetEntity, targetBase);
                    }
                    else if (targetBoundingBox.contains && TestAABB(velocityBoundingBox, velocityTransform, targetBoundingBox, targetTransform))
                    {
                        CollisionCallback(velocityEntity, targetEntity, targetBase);
                    }
                }
            }
        }

        void AddCollisionCallback(
            entt::entity entity, 
            T entityType,
            std::function<void(CollisionInfo)> handler)
        {
            _entityCollisionCallbacks[entity][entityType] = handler;
        }

    private:
        entt::registry& _registry;
        
        //i dunno if this is smart
        std::unordered_map<entt::entity, std::unordered_map<T, std::function<void(CollisionInfo)>>> _entityCollisionCallbacks;

        void CollisionCallback(
                const entt::entity& source, 
                const entt::entity& target, 
                const Global::Components::BaseComponent<T>& targetBase)
        {
            auto entityCollisionHandlers = _entityCollisionCallbacks.find(source);
            if (entityCollisionHandlers == _entityCollisionCallbacks.end())
            {
                return;
            }

            auto collisionHandler = entityCollisionHandlers->second.find(targetBase.entityType);
            if (collisionHandler != entityCollisionHandlers->second.end())
            {
                CollisionInfo collisionInfo;
                collisionInfo.target = target;
                collisionInfo.source = source;
                collisionHandler->second(collisionInfo);
            }
        }

        bool TestAABB(
            const Collision::Components::BoundingBoxComponent& aBoundingBox, const Global::Components::TransformComponent& aTransform,
            const Collision::Components::BoundingBoxComponent& bBoundingBox, const Global::Components::TransformComponent& bTransform)
        {
            glm::vec2 aMax = glm::vec2(aBoundingBox.width + aTransform.position.x, aBoundingBox.height + aTransform.position.y);
            glm::vec2 bMax = glm::vec2(bBoundingBox.width + bTransform.position.x, bBoundingBox.height + bTransform.position.y);

            return bMax.x > aTransform.position.x && bMax.y > aTransform.position.y && aMax.x > bTransform.position.x && aMax.y > bTransform.position.y;
        }
    };
};