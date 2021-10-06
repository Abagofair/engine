#pragma once

#include "External/include//glm/glm.hpp"
#include "External/include/glm/gtc/matrix_transform.hpp"

#include "Engine/include/Scene/Scene.hpp"
#include "Engine/include/Global/Components.hpp"
#include "Engine/include/Collision/CollisionComponents.hpp"
#include "Engine/include/Rendering/RenderingComponents.hpp"
#include "Engine/include/Rendering/Renderable.hpp"
#include "Engine/include/Rendering/ShaderManager.hpp"
#include "Engine/include/Physics/PhysicsComponents.hpp"
#include "Engine/include/Global/Game.hpp"

#include "Generated/EntityType.hpp"
#include "GameComponents.hpp"

namespace Game
{
    class TestScene : public Engine::Scene::Scene
    {
    public:
        TestScene(
            Engine::Global::Game::Game<Game::Generated::EntityType>& game);

        ~TestScene() override = default;

        void Initialize() override;
    private:
        Engine::Global::Game::Game<Game::Generated::EntityType>& _game;

        void CreateViewportBoundingBox();
        void CreateLeftPaddle();
        void CreateRightPaddle();
        void CreateBall();
        void CreateBlocks();
    };
};