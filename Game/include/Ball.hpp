#pragma once

#include <iostream>

#include "External/include/entt/entt.hpp"
#include "External/include/glm/glm.hpp"

#include "Engine/include/Global/Components.hpp"
#include "Engine/include/Collision/CollisionSystem.hpp"
#include "Engine/include/Physics/PhysicsComponents.hpp"
#include "Engine/include/Rendering/RenderingComponents.hpp"

#include "GameComponents.hpp"
#include "Generated/EntityType.hpp"

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