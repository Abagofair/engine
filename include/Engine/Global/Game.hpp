#pragma once

#include <cstdint>

#include <External/entt/entt.hpp>

#include <Engine/Scene/Scene.hpp>
#include <Engine/Windowing/Window.hpp>
#include <Engine/Rendering/ShaderManager.hpp>
#include <Engine/Rendering/BaseRender.hpp>
#include <Engine/Rendering/SpriteRender.hpp>
#include <Engine/Collision/CollisionSystem.hpp>
#include <Engine/Physics/IntegrationSystem.hpp>
#include <Engine/Input/InputHandler.hpp>
#include <Engine/Input/InputStructures.hpp>

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
            : _window(std::make_unique<Engine::Windowing::Window>(width, height, "SHITE")),
                _integrationSystem(Physics::IntegrationSystem(_registry)),
                _collisionSystem(Collision::CollisionSystem<T>(_registry)),
                _render(Rendering::SpriteRender(_registry, _shaderManager, width, height))
        {}

        virtual void Initialize() = 0;
        virtual void Run() = 0;

        const Windowing::Window& GetWindow() const { return *_window; }
        const Rendering::ShaderManager& GetShaderManager() const { return _shaderManager; }
        const Input::InputHandler& GetInputHandler() const { return _inputHandler; }
        const Physics::IntegrationSystem& GetIntegrationSystem() const { return _integrationSystem; }
        const Collision::CollisionSystem<T>& GetCollisionSystem() const { return _collisionSystem; }

        const entt::registry& GetRegistry() { return _registry; }
    protected:
        entt::registry _registry;

        Rendering::SpriteRender _render;
        Input::InputHandler _inputHandler;
        Physics::IntegrationSystem _integrationSystem;
        Collision::CollisionSystem<T> _collisionSystem;
        Rendering::ShaderManager _shaderManager;
        Scene::Scene _currentScene;
        std::unique_ptr<Engine::Windowing::Window> _window;
        GameState _state;
    };
};