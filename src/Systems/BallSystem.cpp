#include <Systems/BallSystem.hpp>

BallSystem::BallSystem(entt::registry& registry)
    : _registry(registry)
{}

void BallSystem::Update()
{
    auto ballView = _registry.view<
        Components::VelocityComponent,
        Components::BallComponent>();
    
    for (auto entity : ballView)
    {
        auto& vel = ballView.get<Components::VelocityComponent>(entity);
        auto& ball = ballView.get<Components::BallComponent>(entity);

        if (ball.ballState == Components::BallState::Launch)
        {
            vel.velocity = glm::vec2(500.0f, -250.f);
            ball.ballState = Components::BallState::Active;
        }
    }
}