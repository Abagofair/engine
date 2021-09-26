#pragma once

#include <iostream>

#include <External/entt/entt.hpp>
#include <External/glm/glm.hpp>

#include <Engine/Input/InputHandler.hpp>
#include <Engine/Input/InputStructures.hpp>
#include <Engine/Collision/CollisionSystem.hpp>
#include <Engine/Global/Components.hpp>

#include <Game/GameComponents.hpp>

namespace Game
{
    class Paddle
    {
    public:
        Paddle(entt::registry& registry);

        void SetPosition(const glm::uvec2& position);

        void MoveLeft(Engine::Input::GamepadEvent gamepadEvent);
        void MoveRight(Engine::Input::GamepadEvent gamepadEvent);

        void LaunchBall(Engine::Input::GamepadEvent gamepadEvent);
        void DebugAttachBall(Engine::Input::GamepadEvent gamepadEvent);

        void Update();

        void OnViewportCollision(Engine::Collision::CollisionInfo collisionInfo);
    private:
        void UpdatePaddle(
            Engine::Physics::Components::VelocityComponent& velocity, 
            Components::LeftPaddleComponent& paddle);
        void Move(
            const Engine::Input::GamepadEvent& gamepadEvent, 
            Components::LeftPaddleComponent& paddle);

        entt::registry& _registry;
    };
};