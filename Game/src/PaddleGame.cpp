#include "../include/PaddleGame.hpp"

namespace Game
{
    PaddleGame::PaddleGame(uint32_t width, uint32_t height)
            : Game(width, height),
              _paddles(_registry),
              _ball(_registry),
              _block(_registry)
    {}

    std::vector<entt::entity> PaddleGame::FindEntities(Generated::EntityType entityType)
    {
        auto view = _registry.view<Engine::Global::Components::BaseComponent<Generated::EntityType>>();

        std::vector<entt::entity> matchingEntities;
        for (auto entity: view)
        {
            auto base = view.get<Engine::Global::Components::BaseComponent<Generated::EntityType>>(entity);
            if (base.entityType == entityType)
            {
                matchingEntities.push_back(entity);
            }
        }
        return matchingEntities;
    }

    void PaddleGame::Initialize()
    {
        _shaderManager.LoadShader("dynamicSprite.glsl", Engine::Rendering::ShaderManager::DYNAMIC_SHADER_NAME);
        _shaderManager.LoadShader("staticSprite.glsl", Engine::Rendering::ShaderManager::STATIC_SHADER_NAME);
        _shaderManager.LoadShader("debug.glsl", Engine::Rendering::ShaderManager::DEBUG_SHADER_NAME);

        _currentScene = std::make_unique<TestScene>(*this);
        _currentScene->Initialize();

        for (auto playerEntity: FindEntities(Generated::EntityType::Paddle))
        {
            _collisionSystem.AddCollisionCallback(playerEntity,
                                                  Generated::EntityType::ViewportContainer,
                                                  std::bind(&Paddle::OnViewportCollision, &_paddles, std::placeholders::_1));
        }

        for (auto ballEntity: FindEntities(Generated::EntityType::Ball))
        {
            _collisionSystem.AddCollisionCallback(ballEntity,
                                                  Generated::EntityType::Block,
                                                  std::bind(&Ball::OnBlockCollision, &_ball, std::placeholders::_1));

            _collisionSystem.AddCollisionCallback(ballEntity,
                                                  Generated::EntityType::Paddle,
                                                  std::bind(&Ball::OnBlockCollision, &_ball, std::placeholders::_1));
            _collisionSystem.AddCollisionCallback(ballEntity,
                                                  Generated::EntityType::ViewportContainer,
                                                  std::bind(&Ball::OnViewportCollision, &_ball, std::placeholders::_1));
        }

        for (auto blockEntity: FindEntities(Generated::EntityType::Block))
        {
            _collisionSystem.AddCollisionCallback(blockEntity,
                                                  Generated::EntityType::Ball,
                                                  std::bind(&Block::OnBallCollision, &_block, std::placeholders::_1));
        }

        _inputHandler.OnGamepadEvent(Engine::Input::GamepadCode::GamepadLeftAxis,
                                     std::bind(&Paddle::MoveLeft, &_paddles, std::placeholders::_1));

        _inputHandler.OnGamepadEvent(Engine::Input::GamepadCode::GamepadRightAxis,
                                     std::bind(&Paddle::MoveRight, &_paddles, std::placeholders::_1));

        _inputHandler.OnGamepadEvent(Engine::Input::GamepadCode::GamepadLeftTrigger,
                                     std::bind(&Paddle::BrakeLeft, &_paddles, std::placeholders::_1));

        _inputHandler.OnGamepadEvent(Engine::Input::GamepadCode::GamepadRightTrigger,
                                     std::bind(&Paddle::BrakeRight, &_paddles, std::placeholders::_1));

        _inputHandler.OnGamepadEvent(Engine::Input::GamepadCode::GamepadButtonA,
                                     std::bind(&Paddle::LaunchBall, &_paddles, std::placeholders::_1));

        _inputHandler.OnGamepadEvent(Engine::Input::GamepadCode::GamepadButtonB,
                                     std::bind(&Paddle::DebugAttachBall, &_paddles, std::placeholders::_1));
    }

    void PaddleGame::Run()
    {
        bool exit = false;
        uint32_t previousTime = SDL_GetTicks();
        Engine::Input::GamepadEvent event;
        _paddles.DebugAttachBall(event);

        while (true)
        {
            auto dynamicRenderablesView = _registry.view<
                    Engine::Global::Components::TransformComponent>();

            Engine::Global::Time::Time time;
            time.MsElapsedTotal = SDL_GetTicks();
            time.MsElapsedFrame = time.MsElapsedTotal - previousTime;
            previousTime = time.MsElapsedTotal;
            time.SecElapsedFrame = time.MsElapsedFrame / 1000.0f;

            _inputHandler.FeedEventQueue();
            _inputHandler.DispatchEvents();
            _paddles.Update();
            _ball.Update();
            _integrationSystem.Integrate(time);
            _collisionSystem.BroadPhase();

            for (auto entity: dynamicRenderablesView)
            {
                auto &transform = dynamicRenderablesView.get<Engine::Global::Components::TransformComponent>(entity);
                //if (sprite.recalculateTransform)
                transform.transform = glm::translate(glm::mat4(1.0f), glm::vec3(transform.position, 0.0f));
                //transform.transform = glm::scale(transform.transform, glm::vec3(10.0f, 60.0f, 0.0f));
            }

            _window->ClearBuffer(Engine::Global::Utilities::RGBA(0.1f, 0.7f, 0.95f, 1.0f));
            _render.DrawStaticQuads();
            _render.Draw();
            _window->SwapBuffers();
        }
    }
};