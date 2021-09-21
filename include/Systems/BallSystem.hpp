#pragma once

#include <entt/entt.hpp>
#include <Systems/CollisionSystem.hpp>
#include <Components.hpp>
#include <glm/glm.hpp>
#include <iostream>

class BallSystem 
{
public:
    BallSystem(entt::registry& registry);

    void Update();

    void OnBlockCollision(CollisionInfo collisionInfo);

private:
    entt::registry& _registry;
};