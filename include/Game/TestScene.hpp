#pragma once

#include <External/glm/glm.hpp>
#include <External/glm/gtc/matrix_transform.hpp>

#include <Engine/Scene/Scene.hpp>
#include <Engine/Global/Components.hpp>
#include <Engine/Collision/CollisionComponents.hpp>
#include <Engine/Rendering/RenderingComponents.hpp>
#include <Engine/Rendering/Renderable.hpp>
#include <Engine/Rendering/ShaderManager.hpp>
#include <Engine/Physics/PhysicsComponents.hpp>
#include <Engine/Global/Game.hpp>

#include <Game/Generated/EntityType.hpp>
#include <Game/GameComponents.hpp>

namespace Game
{
    class TestScene : public Engine::Scene::Scene
    {
    public:
        TestScene(
            Engine::Global::Game::Game<Game::Generated::EntityType>& game);

        void Initialize();
    private:
        Engine::Global::Game::Game<Game::Generated::EntityType>& _game;

        void CreateViewportBoundingBox();
        void CreateLeftPaddle();
        void CreateRightPaddle();
        void CreateBall();
        void CreateBlocks();
    };
};