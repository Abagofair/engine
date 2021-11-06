#pragma once

#include <iostream>
#include <cstdint>

#include "entt/entt.hpp"

#include "Scene/Scene.hpp"
#include "Windowing/Window.hpp"
#include "Rendering/SpriteRendering.hpp"
#include "Collision/CollisionSystem.hpp"
#include "Physics/Integration.hpp"
#include "Input/InputManager.hpp"
#include "Input/InputStructures.hpp"
#include "GUI/GuiManager.hpp"
#include "Resources/ResourceHandler.hpp"

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
            :   _window(std::make_unique<Engine::Windowing::Window>(width, height, "SHITE")),
                _collisionSystem(Collision::CollisionSystem<T>(_registry)),
                _guiManager(_window.get()),
                _inputManager()
        {}

        virtual std::vector<entt::entity> FindEntities(T) = 0;
        virtual void Initialize() = 0;
        virtual void Run() = 0;
        virtual void SceneIsComplete() = 0;

        Windowing::Window& GetWindow() { return *_window; }
        Input::InputManager& GetInputManager() { return _inputManager; }
        Collision::CollisionSystem<T>& GetCollisionSystem() { return _collisionSystem; }

        entt::registry& GetRegistry() { return _registry; }
        Scene::Scene *GetScene() { return _currentScene.get(); }
    protected:
        entt::registry _registry;

        Input::InputManager _inputManager;
        Collision::CollisionSystem<T> _collisionSystem;

        std::unique_ptr<Scene::Scene> _currentScene;
        std::unique_ptr<Engine::Windowing::Window> _window;

        GUI::GuiManager _guiManager;

        GameState _state;
    };
};