#pragma once

#include <iostream>

#include <entt/entt.hpp>
#include <Input/InputHandler.hpp>
#include <Input/InputStructures.hpp>
#include <Components.hpp>

#include <glm/glm.hpp>

class PlayerSystem
{
public:
    PlayerSystem(entt::registry& registry);

    void SetPosition(const glm::uvec2& position);

    void Move(Input::GamepadEvent gamepadEvent);

    void LaunchBall(Input::GamepadEvent gamepadEvent);

private:
    entt::registry& registry;
};