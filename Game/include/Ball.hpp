#pragma once

#include <iostream>

#include "entt/entt.hpp"
#include "glm/glm.hpp"

#include "Global/Components.hpp"
#include "Collision/CollisionSystem.hpp"
#include "Physics/PhysicsComponents.hpp"
#include "Rendering/RenderingComponents.hpp"

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