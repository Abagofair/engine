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

void PlayerSystem::Move(Input::GamepadEvent gamepadEvent)
{
    auto playerView = registry.view<
        Components::VelocityComponent,
        Components::PaddleComponent>();

    auto playerEntity = playerView.front();

    if (playerEntity == entt::null)
    {
        return;
    }

    auto& velocity = playerView.get<Components::VelocityComponent>(playerEntity);
    auto& paddle = playerView.get<Components::PaddleComponent>(playerEntity);


    /*if (gamepadEvent.normalizedAxisValue > 100.0f)
    {
        velocity.velocity.x -= paddle.speed * gamepadEvent.normalizedAxisValue;
    }
    else */if (gamepadEvent.normalizedAxisValue > -10.0f && 
        gamepadEvent.normalizedAxisValue < 0.0f)
    {
        velocity.velocity.x += paddle.speed * gamepadEvent.normalizedAxisValue;
        std::cout << "paddle " << velocity.velocity.x << std::endl;
       // std::cout << "gamepad " << gamepadEvent.normalizedAxisValue << std::endl;
    }
}