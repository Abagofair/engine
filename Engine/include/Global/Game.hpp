#pragma once

#include <cstdint>

#include "External/include/entt/entt.hpp"

#include "Engine/include/Scene/Scene.hpp"
#include "Engine/include/Windowing/Window.hpp"
#include "Engine/include/Rendering/ShaderManager.hpp"
#include "Engine/include/Rendering/BaseRender.hpp"
#include "Engine/include/Rendering/SpriteRender.hpp"
#include "Engine/include/Collision/CollisionSystem.hpp"
#include "Engine/include/Physics/IntegrationSystem.hpp"
#include "Engine/include/Input/InputHandler.hpp"
#include "Engine/include/Input/InputStructures.hpp"

namespace Engine::Global::Game
{
    enum GameState
    {
        Initializing,
        Running,
        Stopping,
        Paused
    };

    //todo: make more composable with better abstract base classes for necessary systems
    template<typename T = int>
    class Game
    {
    public:
        Game(
            uint32_t width,
            uint32_t height
        )
            :   _integrationSystem(Physics::IntegrationSystem(_registry)),
                _window(std::make_unique<Engine::Windowing::Window>(width, height, "SHITE")),
                _render(Rendering::SpriteRender(_registry, _shaderManager, width, height)),
                _collisionSystem(Collision::CollisionSystem<T>(_registry))
        {}

        virtual std::vector<entt::entity> FindEntities(T) = 0;
        virtual void Initialize() = 0;
        virtual void Run() = 0;

        const Windowing::Window& GetWindow() const { return *_window; }
        const Rendering::ShaderManager& GetShaderManager() const { return _shaderManager; }
        const Input::InputHandler& GetInputHandler() const { return _inputHandler; }
        const Physics::IntegrationSystem& GetIntegrationSystem() const { return _integrationSystem; }
        const Collision::CollisionSystem<T>& GetCollisionSystem() const { return _collisionSystem; }

        entt::registry& GetRegistry() { return _registry; }
    protected:
        entt::registry _registry;

        Input::InputHandler _inputHandler;
        Physics::IntegrationSystem _integrationSystem;
        Collision::CollisionSystem<T> _collisionSystem;
        Rendering::ShaderManager _shaderManager;

        Rendering::SpriteRender _render;
        std::unique_ptr<Scene::Scene> _currentScene;
        std::unique_ptr<Engine::Windowing::Window> _window;

        GameState _state;
    };
};