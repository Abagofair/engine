#include "PlayingGameState.hpp"

namespace Game
{
    PlayingGameState::PlayingGameState(Engine::Global::Game::Game<Game::Generated::EntityType> &game)
        :   GameState(game),
            _inputManager(_game.GetInputManager()),
            _collisionSystem(_game.GetCollisionSystem())
    {
    }

    void PlayingGameState::Entering()
    {
        _scene->Initialize();
    }

    void PlayingGameState::Leaving()
    {

    }

    void PlayingGameState::Update(Engine::Global::Time::Time time)
    {
        entt::registry &registry = _game.GetRegistry();

        _inputManager.HandleInput(time);
        Engine::Physics::Integrate(registry, time);
        _collisionSystem.BroadPhase();
    }

    void PlayingGameState::Draw()
    {
        const entt::registry &registry = _game.GetRegistry();
        Engine::Camera::Camera2D *camera = _game.GetScene()->camera;
        if (camera == nullptr)
            return;

        const glm::mat4 &view = camera->viewMatrix;

        Engine::Rendering::DrawStatics(registry, view);
        Engine::Rendering::DrawDynamics(registry, view);
    }
};