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

void BallSystem::OnBlockCollision(CollisionInfo collisionInfo)
{
    std::cout << "COLLIDED" << std::endl;

    auto ballView = _registry.view<
        Components::VelocityComponent,
        Components::LeftPaddleComponent>();

    auto ball = ballView.front();

    auto& v = ballView.get<Components::VelocityComponent>(ball);
    auto& p = ballView.get<Components::LeftPaddleComponent>(ball);

    v.velocity = glm::reflect(v.velocity, glm::normalize(glm::vec2(v.velocity.x*-1.0f, 0.0f)));
}