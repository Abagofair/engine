#include <Systems/PlayerSystem.hpp>

PlayerSystem::PlayerSystem(entt::registry& registry)
    : registry(registry)
{}

void PlayerSystem::SetPosition(const glm::uvec2& position)
{
    auto playerView = registry.view<Components::SpriteComponent>();
    auto playerEntity = playerView.front();

    if (playerEntity == entt::null)
    {
        return;
    }

    auto sprite = playerView.get<Components::SpriteComponent>(playerEntity);

    sprite.position = position;
    sprite.recalculateTransform = true;
}

void PlayerSystem::MoveLeft(Input::GamepadEvent gamepadEvent)
{
    auto leftPaddleView = registry.view<
        Components::VelocityComponent,
        Components::LeftPaddleComponent>();

    auto leftPaddle = leftPaddleView.front();

    auto& v = leftPaddleView.get<Components::VelocityComponent>(leftPaddle);
    auto& p = leftPaddleView.get<Components::LeftPaddleComponent>(leftPaddle);
    Move(gamepadEvent, v, p);
}

void PlayerSystem::MoveRight(Input::GamepadEvent gamepadEvent)
{
    auto rightPaddleView = registry.view<
        Components::VelocityComponent,
        Components::RightPaddleComponent>();

    auto rightPaddle = rightPaddleView.front();

    auto& v1 = rightPaddleView.get<Components::VelocityComponent>(rightPaddle);
    auto& p1 = rightPaddleView.get<Components::RightPaddleComponent>(rightPaddle);
    Move(gamepadEvent, v1, p1);
}

void PlayerSystem::Move(const Input::GamepadEvent& gamepadEvent, Components::VelocityComponent& velocity, 
    Components::LeftPaddleComponent& paddle)
{
    if (gamepadEvent.normalizedMagnitude < 0)
    {
        paddle.state = Components::PaddleState::UP;
        paddle.acceleration = paddle.maxAcceleration * gamepadEvent.normalizedMagnitude;
    }
    else if (gamepadEvent.normalizedMagnitude > 0)
    {
        paddle.state = Components::PaddleState::DOWN;
        paddle.acceleration = paddle.maxAcceleration * gamepadEvent.normalizedMagnitude;
    }
    else
    {
        paddle.acceleration = glm::vec2(0.0f, 0.0f);
        paddle.state = Components::PaddleState::STOP;
    }
}

void PlayerSystem::Update()
{
    auto leftPaddleView = registry.view<
        Components::VelocityComponent,
        Components::LeftPaddleComponent>();

    auto rightPaddleView = registry.view<
        Components::VelocityComponent,
        Components::RightPaddleComponent>();

    auto leftPaddle = leftPaddleView.front();
    auto rightPaddle = rightPaddleView.front();

    auto& v = leftPaddleView.get<Components::VelocityComponent>(leftPaddle);
    auto& p = leftPaddleView.get<Components::LeftPaddleComponent>(leftPaddle);
    UpdatePaddle(v, p);

    auto& v1 = rightPaddleView.get<Components::VelocityComponent>(rightPaddle);
    auto& p1 = rightPaddleView.get<Components::RightPaddleComponent>(rightPaddle);
    UpdatePaddle(v1, p1);
}

void PlayerSystem::UpdatePaddle(Components::VelocityComponent& velocity, Components::LeftPaddleComponent& paddle)
{
    if (paddle.state == Components::PaddleState::STOP)
    {
        glm::vec2 accel = glm::abs(paddle.acceleration);
        const float decel = accel.y * 0.0000001f;

        if (paddle.acceleration.y < 0.0f)
            paddle.acceleration.y += decel;
        else if (paddle.acceleration.y > 0.0f)
            paddle.acceleration.y -= decel;

        /*if (accel.y < 0.000005f)
            paddle.acceleration.y = 0.0f;*/
    }
        
    velocity.velocity += paddle.acceleration;
    
    glm::vec2 copy = glm::abs(velocity.velocity);
    if (copy.x > paddle.velocityCeiling.x)
        velocity.velocity.x = velocity.velocity.x > 0 ? paddle.velocityCeiling.x : -paddle.velocityCeiling.x;
    if (copy.y > paddle.velocityCeiling.y)
        velocity.velocity.y = velocity.velocity.y > 0 ? paddle.velocityCeiling.y : -paddle.velocityCeiling.y;
}