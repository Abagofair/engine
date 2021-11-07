#include "PaddleGame.hpp"

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
        Engine::Global::Utilities::Logger::WriteInfo("Initializing game..", "");

        Engine::Resources::LoadShader("dynamicSprite.glsl", Engine::Resources::DYNAMIC_SHADER_NAME);
        Engine::Resources::LoadShader("staticSprite.glsl", Engine::Resources::STATIC_SHADER_NAME);
        Engine::Resources::LoadShader("debug.glsl", Engine::Resources::DEBUG_SHADER_NAME);

        _currentState = std::make_unique<PlayingGameState>(*this);
        _currentState->Entering();
    }

    [[noreturn]] void PaddleGame::Run()
    {
        _guiManager.LoadInGameMenuDocument();

        bool exit = false;
        uint32_t previousTime = SDL_GetTicks();

        while (true)
        {
            Engine::Global::Time::Time time;
            time.MsElapsedTotal = SDL_GetTicks();
            time.MsElapsedFrame = time.MsElapsedTotal - previousTime;
            previousTime = time.MsElapsedTotal;
            time.SecElapsedFrame = time.MsElapsedFrame / 1000.0f;

            _currentState->Update(time);

            auto dynamicRenderablesView = _registry.view<
                    Engine::Global::Components::TransformComponent>();

            for (auto entity: dynamicRenderablesView)
            {
                auto &transform = dynamicRenderablesView.get<Engine::Global::Components::TransformComponent>(entity);
                //if (sprite.recalculateTransform)
                transform.transform = glm::translate(glm::mat4(1.0f), glm::vec3(transform.position, 0.0f));
                //transform.transform = glm::scale(transform.transform, glm::vec3(10.0f, 60.0f, 0.0f));
            }

            _currentState->Draw();
        }
    }

    void PaddleGame::SceneIsComplete()
    {

    }
};