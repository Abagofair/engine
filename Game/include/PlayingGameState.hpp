#pragma once

#include <memory>

#include "GameState.hpp"

#include "Generated/EntityType.hpp"
#include "Global/Game.hpp"
#include "Global/Time/Time.hpp"
#include "Scene/Scene.hpp"
#include "Input/InputManager.hpp"
#include "Physics/Integration.hpp"
#include "Collision/CollisionSystem.hpp"
#include "Rendering/SpriteRendering.hpp"

#include "Paddle.hpp"
#include "Ball.hpp"
#include "Block.hpp"
#include "TestScene.hpp"

namespace Game
{
    class PlayingGameState : public GameState
    {
    public:
        explicit PlayingGameState(Engine::Global::Game::Game<Game::Generated::EntityType> &game);
        ~PlayingGameState() = default;

        void Entering() override;
        void Leaving() override;

        void Update(Engine::Global::Time::Time time) override;
        void Draw() override;

    private:
        Game::Paddle _paddleSystem;
        Game::Ball _ballSystem;
        Game::Block _blockSystem;

        Engine::Input::InputManager& _inputManager;
        Engine::Collision::CollisionSystem<Game::Generated::EntityType>& _collisionSystem;

        void PauseMenu(Engine::Input::KeyEvent);
        void SceneIsComplete();
    };
};