#pragma once

#include "External/include/entt/entt.hpp"

#include "Engine/include/Collision/CollisionSystem.hpp"
#include "Engine/include/Rendering/RenderingComponents.hpp"
#include "Engine/include/Global/Components.hpp"

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