#pragma once

#include <iostream>

#include <External/entt/entt.hpp>
#include <External/glm/glm.hpp>

#include <Engine/Global/Components.hpp>
#include <Engine/Collision/CollisionSystem.hpp>
#include <Engine/Physics/PhysicsComponents.hpp>

#include <Game/GameComponents.hpp>

namespace Game
{
    class Ball 
    {
    public:
        Ball(entt::registry& registry);

        void Update();

        void OnBlockCollision(Engine::Collision::CollisionInfo collisionInfo);
        void OnViewportCollision(Engine::Collision::CollisionInfo collisionInfo);

    private:
        entt::registry& _registry;
    };
};