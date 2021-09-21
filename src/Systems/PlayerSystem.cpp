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

void PlayerSystem::LaunchBall(Input::GamepadEvent gamepadEvent)
{
    auto leftPaddleView = registry.view<
        Components::VelocityComponent,
        Components::LeftPaddleComponent>();

    auto leftPaddle = leftPaddleView.front();
    auto& p = leftPaddleView.get<Components::LeftPaddleComponent>(leftPaddle);

    if (p.attached == entt::null) return;

    auto& vBall = registry.get<Components::BallComponent>(p.attached);

    if (gamepadEvent.inputEventType == Input::InputEventType::GamePadButtonDown &&
        vBall.ballState == Components::BallState::Attached)
    {
        vBall.ballState = Components::BallState::Launch;
        p.attached = entt::null;
    }
}

void PlayerSystem::DebugAttachBall(Input::GamepadEvent gamepadEvent)
{
    auto leftPaddleView = registry.view<
        Components::LeftPaddleComponent,
        Components::SpriteComponent>();

    auto leftPaddle = leftPaddleView.front();
    auto& p = leftPaddleView.get<Components::LeftPaddleComponent>(leftPaddle);
    auto& playerSprite = leftPaddleView.get<Components::SpriteComponent>(leftPaddle);

    auto ballView = registry.view<
        Components::BallComponent,
        Components::VelocityComponent,
        Components::SpriteComponent>();
    auto ball = ballView.front();

    auto& ballComp = ballView.get<Components::BallComponent>(ball);
    auto& ballVelocity = ballView.get<Components::VelocityComponent>(ball);
    auto& ballSprite = ballView.get<Components::SpriteComponent>(ball);

    ballSprite.position = glm::vec2(playerSprite.position.x + 20.0f, playerSprite.position.y);
    ballVelocity.velocity = glm::vec2(0.0f, 0.0f);
    ballComp.ballState = Components::BallState::Attached;
    p.attached = ball;
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

    if (p.attached != entt::null)
    {
        auto& vBall = registry.get<Components::VelocityComponent>(p.attached);
        vBall.velocity = v.velocity;
    }

    if (p1.attached != entt::null)
    {
        auto& vBall = registry.get<Components::VelocityComponent>(p.attached);
        vBall.velocity = v.velocity;
    }
}

void PlayerSystem::UpdatePaddle(Components::VelocityComponent& velocity, Components::LeftPaddleComponent& paddle)
{
    if (paddle.state == Components::PaddleState::STOP)
    {
        glm::vec2 accel = glm::abs(velocity.velocity);
        const float decel = accel.y * 0.005f;

        if (velocity.velocity.y < 0.0f)
            velocity.velocity.y += decel;
        else if (velocity.velocity.y > 0.0f)
            velocity.velocity.y -= decel;
    }
    
    velocity.velocity += paddle.acceleration;
}