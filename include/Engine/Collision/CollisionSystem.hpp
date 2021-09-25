#pragma once

#include <unordered_map>

#include <External/entt/entt.hpp>
#include <External/glm/glm.hpp>

#include <Engine/Global/Components.hpp>
#include <Engine/Global/Generated/Types.hpp>
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

    class CollisionSystem
    {
    public:
        CollisionSystem(
            entt::registry& registry
        );

        void Handle();
        
        void AddCollisionHandler(
            entt::entity entity, 
            Global::Generated::EntityType entityType, 
            std::function<void(CollisionInfo)> handler
        );

    private:
        entt::registry& _registry;
        
        //i dunno if this is smart
        std::unordered_map<
            entt::entity,
            std::unordered_map<Global::Generated::EntityType, 
                std::function<void(CollisionInfo)>>> _entityCollisionHandlers;

        bool TestAABB(const Collision::Components::BoundingBoxComponent& a, 
            const Collision::Components::BoundingBoxComponent& b);
    };
};