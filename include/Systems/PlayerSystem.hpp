#pragma once

#include <iostream>

#include <entt/entt.hpp>

#include <Input/InputHandler.hpp>
#include <Input/InputStructures.hpp>
#include <Components.hpp>

#include <Systems/CollisionSystem.hpp>

#include <glm/glm.hpp>

class PlayerSystem
{
public:
    PlayerSystem(entt::registry& registry);

    void SetPosition(const glm::uvec2& position);

    void MoveLeft(Input::GamepadEvent gamepadEvent);
    void MoveRight(Input::GamepadEvent gamepadEvent);

    void LaunchBall(Input::GamepadEvent gamepadEvent);
    void DebugAttachBall(Input::GamepadEvent gamepadEvent);

    void Update();

private:
    void UpdatePaddle(Components::VelocityComponent& velocity, Components::LeftPaddleComponent& paddle);
    void Move(const Input::GamepadEvent& gamepadEvent, Components::VelocityComponent& velocity, 
        Components::LeftPaddleComponent& paddle);

    entt::registry& registry;
};