#pragma once

#include "entt/entt.hpp"

#include "Collision/CollisionSystem.hpp"
#include "Rendering/RenderingComponents.hpp"
#include "Global/Components.hpp"

#include "Generated/EntityType.hpp"
#include "GameComponents.hpp"

namespace Game
{
    class Block
    {
    public:
        Block(entt::registry& registry);

        void OnBallCollision(Engine::Collision::CollisionInfo collisionInfo);

    private:
        entt::registry& _registry;
    };
};