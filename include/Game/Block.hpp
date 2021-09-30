#pragma once

#include <External/entt/entt.hpp>

#include <Engine/Collision/CollisionSystem.hpp>
#include <Engine/Rendering/RenderingComponents.hpp>
#include <Engine/Global/Components.hpp>

#include <Game/Generated/EntityType.hpp>

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