#include <Game/Paddle.hpp>

namespace Game
{
    Paddle::Paddle(entt::registry& registry)
        : _registry(registry)
    {}

    void Paddle::SetPosition(const glm::uvec2& position)
    {
        auto playerView = _registry.view<Engine::Global::Components::TransformComponent>();
        auto playerEntity = playerView.front();

        if (playerEntity == entt::null)
        {
            return;
        }

        auto sprite = playerView.get<Engine::Global::Components::TransformComponent>(playerEntity);

        sprite.position = position;
        sprite.recalculateTransform = true;
    }

    void Paddle::MoveLeft(Engine::Input::GamepadEvent gamepadEvent)
    {
        auto leftPaddleView = _registry.view<
            Engine::Physics::Components::VelocityComponent,
            Components::LeftPaddleComponent>();

        auto leftPaddle = leftPaddleView.front();

        auto& v = leftPaddleView.get<Engine::Physics::Components::VelocityComponent>(leftPaddle);
        auto& p = leftPaddleView.get<Components::LeftPaddleComponent>(leftPaddle);
        Move(gamepadEvent, v, p);
    }

    void Paddle::MoveRight(Engine::Input::GamepadEvent gamepadEvent)
    {
        auto rightPaddleView = _registry.view<
            Engine::Physics::Components::VelocityComponent,
            Components::RightPaddleComponent>();

        auto rightPaddle = rightPaddleView.front();

        auto& v1 = rightPaddleView.get<Engine::Physics::Components::VelocityComponent>(rightPaddle);
        auto& p1 = rightPaddleView.get<Components::RightPaddleComponent>(rightPaddle);
        Move(gamepadEvent, v1, p1);
    }

    void Paddle::Move(
        const Engine::Input::GamepadEvent& gamepadEvent, 
        Engine::Physics::Components::VelocityComponent& velocity, 
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

    void Paddle::LaunchBall(Engine::Input::GamepadEvent gamepadEvent)
    {
        auto leftPaddleView = _registry.view<
            Engine::Physics::Components::VelocityComponent,
            Components::LeftPaddleComponent>();

        auto leftPaddle = leftPaddleView.front();
        auto& p = leftPaddleView.get<Components::LeftPaddleComponent>(leftPaddle);

        if (p.attached == entt::null) return;

        auto& vBall = _registry.get<Components::BallComponent>(p.attached);

        if (gamepadEvent.inputEventType == Engine::Input::InputEventType::GamePadButtonDown &&
            vBall.ballState == Components::BallState::Attached)
        {
            vBall.ballState = Components::BallState::Launch;
            p.attached = entt::null;
        }
    }

    void Paddle::DebugAttachBall(Engine::Input::GamepadEvent gamepadEvent)
    {
        auto leftPaddleView = _registry.view<
            Components::LeftPaddleComponent,
            Engine::Global::Components::TransformComponent>();

        auto leftPaddle = leftPaddleView.front();
        auto& p = leftPaddleView.get<Components::LeftPaddleComponent>(leftPaddle);
        auto& playerSprite = leftPaddleView.get<Engine::Global::Components::TransformComponent>(leftPaddle);

        auto ballView = _registry.view<
            Components::BallComponent,
            Engine::Physics::Components::VelocityComponent,
            Engine::Global::Components::TransformComponent>();
        auto ball = ballView.front();

        auto& ballComp = ballView.get<Components::BallComponent>(ball);
        auto& ballVelocity = ballView.get<Engine::Physics::Components::VelocityComponent>(ball);
        auto& ballSprite = ballView.get<Engine::Global::Components::TransformComponent>(ball);

        ballSprite.position = glm::vec2(playerSprite.position.x + 20.0f, playerSprite.position.y);
        ballVelocity.velocity = glm::vec2(0.0f, 0.0f);
        ballComp.ballState = Components::BallState::Attached;
        p.attached = ball;
    }

    void Paddle::Update()
    {
        auto leftPaddleView = _registry.view<
            Engine::Physics::Components::VelocityComponent,
            Components::LeftPaddleComponent>();

        auto rightPaddleView = _registry.view<
            Engine::Physics::Components::VelocityComponent,
            Components::RightPaddleComponent>();

        auto leftPaddle = leftPaddleView.front();
        auto rightPaddle = rightPaddleView.front();

        auto& v = leftPaddleView.get<Engine::Physics::Components::VelocityComponent>(leftPaddle);
        auto& p = leftPaddleView.get<Components::LeftPaddleComponent>(leftPaddle);
        UpdatePaddle(v, p);

        auto& v1 = rightPaddleView.get<Engine::Physics::Components::VelocityComponent>(rightPaddle);
        auto& p1 = rightPaddleView.get<Components::RightPaddleComponent>(rightPaddle);
        UpdatePaddle(v1, p1);

        if (p.attached != entt::null)
        {
            auto& vBall = _registry.get<Engine::Physics::Components::VelocityComponent>(p.attached);
            vBall.velocity = v.velocity;
        }

        if (p1.attached != entt::null)
        {
            auto& vBall = _registry.get<Engine::Physics::Components::VelocityComponent>(p.attached);
            vBall.velocity = v.velocity;
        }
    }

    void Paddle::UpdatePaddle(
        Engine::Physics::Components::VelocityComponent& velocity, 
        Components::LeftPaddleComponent& paddle)
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
};