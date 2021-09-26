#include <Game/Ball.hpp>

namespace Game
{
    Ball::Ball(entt::registry& registry)
        : _registry(registry)
    {}

    void Ball::Update()
    {
        auto ballView = _registry.view<
            Engine::Physics::Components::VelocityComponent,
            Components::BallComponent>();
        
        for (auto entity : ballView)
        {
            auto& vel = ballView.get<Engine::Physics::Components::VelocityComponent>(entity);
            auto& ball = ballView.get<Components::BallComponent>(entity);

            if (ball.ballState == Components::BallState::Launch)
            {
                vel.velocity = glm::vec2(500.0f, -250.f);
                ball.ballState = Components::BallState::Active;
            }
        }
    }

    void Ball::OnBlockCollision(Engine::Collision::CollisionInfo collisionInfo)
    {
        auto& collidedSprite = _registry.get<
            Engine::Global::Components::TransformComponent>(collisionInfo.target);
        auto& collidedBoundingBox = _registry.get<
            Engine::Collision::Components::BoundingBoxComponent>(collisionInfo.target);
        
        auto& collidedBase = _registry.get<
            Engine::Global::Components::BaseComponent<Game::Generated::EntityType>>(collisionInfo.target);

        auto& collidedState = _registry.get<
            Engine::Global::Components::EntityStateComponent>(collisionInfo.target);

        //todo: signal something something scene state instead so we can handle multiple things separately
        if (collidedBase.entityType == Game::Generated::Block)
        {
            //GameManager.SetEntityState(entt::entity entity)
            collidedState.active = false;
        }

        auto ballView = _registry.view<
            Engine::Physics::Components::VelocityComponent,
            Engine::Global::Components::TransformComponent,
            Engine::Collision::Components::BoundingBoxComponent>();

        auto ball = ballView.front();

        auto& v = ballView.get<Engine::Physics::Components::VelocityComponent>(ball);
        auto& s = ballView.get<Engine::Global::Components::TransformComponent>(ball);
        auto& b = ballView.get<Engine::Collision::Components::BoundingBoxComponent>(ball);

        glm::vec2 collidedCenter = glm::vec2(
            collidedSprite.position.x + (collidedBoundingBox.width / 2.0f),
            collidedSprite.position.y + (collidedBoundingBox.height / 2.0f));

        glm::vec2 up = glm::vec2(
            collidedSprite.position.x + (collidedBoundingBox.width / 2.0f),
            -1.0f);

        glm::vec2 ballCenter = glm::vec2(
            s.position.x + (b.width / 2.0f),
            s.position.y + (b.height / 2.0f));

        float dot = glm::dot(up, ballCenter - collidedCenter);
        
        if (dot <= 0)
            s.position.x = collidedSprite.position.x - collidedBoundingBox.width;
        else
            s.position.x = collidedSprite.position.x + collidedBoundingBox.width;

        v.velocity = glm::reflect(v.velocity, glm::normalize(glm::vec2(v.velocity.x*-1.0f, 0.0f)));
    }

    void Ball::OnViewportCollision(Engine::Collision::CollisionInfo collisionInfo)
    {
        auto& boundingBox = _registry.get<Engine::Collision::Components::BoundingBoxComponent>(collisionInfo.target);

        auto& transform = _registry.get<Engine::Global::Components::TransformComponent>(collisionInfo.source);
        auto& sourceBoundingBox = _registry.get<Engine::Collision::Components::BoundingBoxComponent>(collisionInfo.source);
        auto& velocity = _registry.get<Engine::Physics::Components::VelocityComponent>(collisionInfo.source);

        if (transform.position.y < 0.0f)
        {
            velocity.velocity.y *= -1;
            transform.position.y = 0.0f;
        }
        else if (transform.position.y > (boundingBox.height - sourceBoundingBox.height))
        {
            velocity.velocity.y *= -1;
            transform.position.y = boundingBox.height - sourceBoundingBox.height;
        }
    }
};