#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Scene/Scene.hpp"
#include "Global/Components.hpp"
#include "Collision/CollisionComponents.hpp"
#include "Rendering/RenderingComponents.hpp"
#include "Rendering/RenderingStructures.hpp"
#include "Rendering/Renderable.hpp"
#include "Physics/PhysicsComponents.hpp"
#include "Global/Game.hpp"

#include "Resources/ResourceHandler.hpp"

#include "Generated/EntityType.hpp"
#include "GameComponents.hpp"

namespace Game
{
    class TestScene : public Engine::Scene::Scene
    {
    public:
        TestScene(Engine::Global::Game::Game<Game::Generated::EntityType>& game);

        ~TestScene() override = default;

        void Initialize() override;
        void CheckSceneState() override;
    private:
        Engine::Global::Game::Game<Game::Generated::EntityType>& _game;

        void CreateViewportBoundingBox();
        void CreateLeftPaddle();
        void CreateRightPaddle();
        void CreateBall();
        void CreateBlocks();
    };
};