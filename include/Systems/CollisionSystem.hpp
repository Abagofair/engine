#pragma once

#include <unordered_map>

#include <entt/entt.hpp>

#include <glm/glm.hpp>

#include <Window.hpp>
#include <Components.hpp>

#include <iostream>

struct CollisionInfo
{
    entt::entity collisionEntity;
};

class CollisionSystem
{
public:
    CollisionSystem(entt::registry& registry,
        Window& Window);

    void HandleViewport();
    
    void AddCollisionHandler(
        entt::entity entity, 
        Components::EntityType entityType, 
        std::function<void(CollisionInfo)> handler
    );

private:
    entt::registry& _registry;
    Window& _window;
    
    //i dunno if this is smart
    std::unordered_map<entt::entity,
        std::unordered_map<Components::EntityType, std::function<void(CollisionInfo)>>> _entityCollisionHandlers;

    bool TestAABB(const Components::BoundingBoxComponent& a, const Components::BoundingBoxComponent& b);
};