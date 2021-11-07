#include "PlayingGameState.hpp"

namespace Game
{
    PlayingGameState::PlayingGameState(Engine::Global::Game::Game<Game::Generated::EntityType> &game)
        :   GameState(game),
            _inputManager(_game.GetInputManager()),
            _collisionSystem(_game.GetCollisionSystem()),
            _paddleSystem(_game.GetRegistry()),
            _ballSystem(_game.GetRegistry()),
            _blockSystem(_game.GetRegistry())
    {
    }

    void PlayingGameState::Entering()
    {
        std::vector<Engine::Input::Action<Engine::Input::KeyEvent>> m =
        {
            SHITE_INPUT_GAMEPAD_ACTION("PauseMenu", KeyEvent, PauseMenu)
        };

        _inputManager.InitializeActionsFromDisk(_paddleSystem.GetGamepadActions(), m);

        auto scene = std::make_unique<Game::TestScene>(_game);
        scene->Initialize();
        _game.SetCurrentScene(std::move(scene));

        for (auto playerEntity : _game.FindEntities(Generated::EntityType::Paddle))
        {
            _collisionSystem.AddCollisionCallback(playerEntity,
                                                  Generated::EntityType::ViewportContainer,
                                                  std::bind(&Paddle::OnViewportCollision, &_paddleSystem, std::placeholders::_1));
        }

        for (auto ballEntity : _game.FindEntities(Generated::EntityType::Ball))
        {
            _collisionSystem.AddCollisionCallback(ballEntity,
                                                  Generated::EntityType::Block,
                                                  std::bind(&Ball::OnBlockCollision, &_ballSystem, std::placeholders::_1));

            _collisionSystem.AddCollisionCallback(ballEntity,
                                                  Generated::EntityType::Paddle,
                                                  std::bind(&Ball::OnBlockCollision, &_ballSystem, std::placeholders::_1));
            _collisionSystem.AddCollisionCallback(ballEntity,
                                                  Generated::EntityType::ViewportContainer,
                                                  std::bind(&Ball::OnViewportCollision, &_ballSystem, std::placeholders::_1));
        }

        for (auto blockEntity : _game.FindEntities(Generated::EntityType::Block))
        {
            _collisionSystem.AddCollisionCallback(blockEntity,
                                                  Generated::EntityType::Ball,
                                                  std::bind(&Block::OnBallCollision, &_blockSystem, std::placeholders::_1));
        }

        /*_inputContext.OnGamepadEvent(Engine::Input::GamepadCode::GamepadLeftAxis,
                                     std::bind(&Paddle::MoveLeft, &_paddles, std::placeholders::_1));

        _inputContext.OnGamepadEvent(Engine::Input::GamepadCode::GamepadRightAxis,
                                     std::bind(&Paddle::MoveRight, &_paddles, std::placeholders::_1));

        _inputContext.OnGamepadEvent(Engine::Input::GamepadCode::GamepadLeftTrigger,
                                     std::bind(&Paddle::BrakeLeft, &_paddles, std::placeholders::_1));

        _inputContext.OnGamepadEvent(Engine::Input::GamepadCode::GamepadRightTrigger,
                                     std::bind(&Paddle::BrakeRight, &_paddles, std::placeholders::_1));

        _inputContext.OnGamepadEvent(Engine::Input::GamepadCode::GamepadButtonA,
                                     std::bind(&Paddle::LaunchBall, &_paddles, std::placeholders::_1));

        _inputContext.OnGamepadEvent(Engine::Input::GamepadCode::GamepadButtonB,
                                     std::bind(&Paddle::DebugAttachBall, &_paddles, std::placeholders::_1));*/
    }

    void PlayingGameState::Leaving()
    {

    }

    void PlayingGameState::Update(Engine::Global::Time::Time time)
    {
        entt::registry &registry = _game.GetRegistry();

        _inputManager.HandleInput(time);

        _paddleSystem.Update();
        _ballSystem.Update();

        Engine::Physics::Integrate(registry, time);
        _collisionSystem.BroadPhase();
    }

    void PlayingGameState::Draw()
    {
        _game.GetWindow().ClearBuffer(Engine::Global::Utilities::RGBA(0.1f, 0.7f, 0.95f, 1.0f));

        const entt::registry &registry = _game.GetRegistry();
        Engine::Camera::Camera2D *camera = _game.GetScene()->camera;

        if (camera == nullptr)
            return;

        const glm::mat4 &view = camera->viewMatrix;

        Engine::Rendering::DrawStatics(registry, view);
        Engine::Rendering::DrawDynamics(registry, view);

        _game.GetWindow().SwapBuffers();
    }

    void PlayingGameState::SceneIsComplete()
    {
        std::cout << "SCENE IS COMPLETE" << std::endl;
    }

    void PlayingGameState::PauseMenu(Engine::Input::KeyEvent)
    {
        std::cout << "PAUSING" << std::endl;

        /*    _state = Engine::Global::Game::GameState::Paused;
        else if (_state == Engine::Global::Game::GameState::Paused)
            _state = Engine::Global::Game::GameState::Running;*/
    }
};