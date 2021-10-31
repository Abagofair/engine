#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <string>

#include "entt/entt.hpp"
#include "glm/glm.hpp"

#include "Physics/PhysicsComponents.hpp"
#include "Input/SDLInputHandler.hpp"
#include "Input/InputStructures.hpp"
#include "Collision/CollisionSystem.hpp"
#include "Global/Components.hpp"

#include "GameComponents.hpp"
#include "Generated/EntityType.hpp"

namespace Game
{
    class Paddle
    {
    public:
        Paddle(entt::registry& registry);

        void SetPosition(const glm::uvec2& position);

        void Update();

        void OnViewportCollision(Engine::Collision::CollisionInfo collisionInfo);

        [[nodiscard]] const std::vector<Engine::Input::Action<Engine::Input::GamepadEvent>>& GetGamepadActions() const;
    private:
        std::vector<Engine::Input::Action<Engine::Input::GamepadEvent>> _actions =
        {
            SHITE_INPUT_GAMEPAD_ACTION("BrakeLeft", GamepadEvent, BrakeLeft)
            SHITE_INPUT_GAMEPAD_ACTION("BrakeRight", GamepadEvent, BrakeRight)
            SHITE_INPUT_GAMEPAD_ACTION("MoveLeft", GamepadEvent, MoveLeft)
            SHITE_INPUT_GAMEPAD_ACTION("MoveRight", GamepadEvent, MoveRight)
            SHITE_INPUT_GAMEPAD_ACTION("LaunchBall", GamepadEvent, LaunchBall)
            SHITE_INPUT_GAMEPAD_ACTION("DebugAttachBall", GamepadEvent, DebugAttachBall)
        };

        void BrakeLeft(Engine::Input::GamepadEvent gamepadEvent);
        void BrakeRight(Engine::Input::GamepadEvent gamepadEvent);
        void MoveLeft(Engine::Input::GamepadEvent gamepadEvent);
        void MoveRight(Engine::Input::GamepadEvent gamepadEvent);
        void LaunchBall(Engine::Input::GamepadEvent gamepadEvent);
        void DebugAttachBall(Engine::Input::GamepadEvent gamepadEvent);

        void UpdatePaddle(
            Engine::Physics::Components::VelocityComponent& velocity, 
            Components::LeftPaddleComponent& paddle);
        void Move(
            const Engine::Input::GamepadEvent& gamepadEvent, 
            Components::LeftPaddleComponent& paddle);

        entt::registry& _registry;
        Game::Generated::EntityType _entityType;
    };
};