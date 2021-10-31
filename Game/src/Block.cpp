#include "Block.hpp"

namespace Game
{
    Block::Block(entt::registry& registry)
        : _registry(registry)
    {}

    void Block::OnBallCollision(Engine::Collision::CollisionInfo collisionInfo)
    {
        auto& collidedBase = _registry.get<
                Engine::Global::Components::BaseComponent<Generated::EntityType>>(collisionInfo.source);
        auto& collidedBB = _registry.get<
                Engine::Collision::Components::BoundingBoxComponent>(collisionInfo.source);
        auto& instancedQuadComponent = _registry.get<
                Engine::Rendering::Components::InstancedQuadComponent>(collisionInfo.source);

        auto& block = _registry.get<Game::Components::BlockComponent>(collisionInfo.source);

        block.blockState = Components::BlockState::Dead;
        collidedBB.ignoreCollisions = true;
        instancedQuadComponent.ignore = true;
    }
};