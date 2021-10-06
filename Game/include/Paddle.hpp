#pragma once

#include <iostream>

#include "External/include/entt/entt.hpp"
#include "External/include/glm/glm.hpp"

#include "Engine/include/Physics/PhysicsComponents.hpp"
#include "Engine/include/Input/InputHandler.hpp"
#include "Engine/include/Input/InputStructures.hpp"
#include "Engine/include/Collision/CollisionSystem.hpp"
#include "Engine/include/Global/Components.hpp"

#include "GameComponents.hpp"
#include "Generated/EntityType.hpp"

namespace Game
{
    class Paddle
    {
    public:
        Paddle(entt::registry& registry);

        void SetPosition(const glm::uvec2& position);

        void BrakeLeft(Engine::Input::GamepadEvent gamepadEvent);
        void BrakeRight(Engine::Input::GamepadEvent gamepadEvent);
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
        Game::Generated::EntityType _entityType;
    };
};