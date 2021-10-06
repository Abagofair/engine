#include "../include/Block.hpp"

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

        collidedBB.ignoreCollisions = true;
        instancedQuadComponent.ignore = true;
    }
};