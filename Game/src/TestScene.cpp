#include "../include/TestScene.hpp"

namespace Game
{
    TestScene::TestScene(
        Engine::Global::Game::Game<Game::Generated::EntityType>& game)
        : _game(game)
    {
    }

    void TestScene::Initialize()
    {
        CreateViewportBoundingBox();
        CreateLeftPaddle();
        CreateRightPaddle();
        CreateBall();
        CreateBlocks();
    }

    void TestScene::CheckSceneState()
    {
        auto blockStateView = _game.GetRegistry().view<
                Game::Components::BlockComponent>();

        for (auto entity : blockStateView)
        {
            auto& blockState = blockStateView.get<Game::Components::BlockComponent>(entity);

            if (blockState.blockState == Components::BlockState::Live)
                return;
        }

        //all blocks are dead here
        //signal game that the scene goal has been reached
        _game.SceneIsComplete();
    }

    void TestScene::CreateViewportBoundingBox()
    {
        auto viewportEntity = _game.GetRegistry().create();
        auto& viewportBase = _game.GetRegistry().emplace<Engine::Global::Components::BaseComponent<Game::Generated::EntityType>>(viewportEntity);
        auto& viewportBB = _game.GetRegistry().emplace<Engine::Collision::Components::BoundingBoxComponent>(viewportEntity);
        auto& viewportTran = _game.GetRegistry().emplace<Engine::Global::Components::TransformComponent>(viewportEntity);

        viewportBase.entityType = Game::Generated::EntityType::ViewportContainer;
        viewportBB.contains = true;
        viewportBB.width = 1920;
        viewportBB.height = 1080;

        viewportTran.position = glm::vec3(0.0);
        viewportTran.transform = glm::mat4(1.0f);
    }

    void TestScene::CreateLeftPaddle()
    {
        auto leftPaddleEntity = _game.GetRegistry().create();
        auto& d = _game.GetRegistry().emplace<Engine::Rendering::Components::RenderableComponent>(leftPaddleEntity);
        auto& p = _game.GetRegistry().emplace<Game::Components::LeftPaddleComponent>(leftPaddleEntity);
        auto& s = _game.GetRegistry().emplace<Engine::Global::Components::TransformComponent>(leftPaddleEntity);
        auto& v = _game.GetRegistry().emplace<Engine::Physics::Components::VelocityComponent>(leftPaddleEntity);
        auto& b = _game.GetRegistry().emplace<Engine::Collision::Components::BoundingBoxComponent>(leftPaddleEntity);
        auto& leftPaddleBase = _game.GetRegistry().emplace<Engine::Global::Components::BaseComponent<Game::Generated::EntityType>>(leftPaddleEntity);
        leftPaddleBase.entityType = Game::Generated::EntityType::Paddle;

        auto& state = _game.GetRegistry().emplace<Engine::Global::Components::EntityStateComponent>(leftPaddleEntity);
        state.active = true;

        p.maxAcceleration = glm::vec2(0.0f, 50.0f);
        p.velocityCeiling = glm::vec2(0.0f, 50.0f);
        v.velocity.x = 0.0f;
        v.velocity.y = 0.0f;
        b.height = 60;
        b.width = 10;
        s.position.x = 10.0f;
        s.position.y = 0.0f;
        s.recalculateTransform = false;

        glm::mat4 trans = glm::mat4(1.0f);
        s.transform = glm::translate(glm::mat4(1.0f), glm::vec3(s.position, 0.0f));
        s.transform = glm::scale(s.transform, glm::vec3(10.0f, 60.0f, 0.0f));

        auto& shader  = _game.GetShaderManager().GetShader(Engine::Rendering::ShaderManager::DYNAMIC_SHADER_NAME);

        //auto tex = _game.GetTextureManager().TextureFromImage("paddle.png");

        d = Engine::Rendering::SetupDynamic(0, shader.ShaderId(), b.width, b.height);
    }

    void TestScene::CreateRightPaddle()
    {
        auto rightPaddleEntity = _game.GetRegistry().create();
        auto& d1 = _game.GetRegistry().emplace<Engine::Rendering::Components::RenderableComponent>(rightPaddleEntity);
        auto& s1 = _game.GetRegistry().emplace<Engine::Global::Components::TransformComponent>(rightPaddleEntity);
        auto& p1 = _game.GetRegistry().emplace<Game::Components::RightPaddleComponent>(rightPaddleEntity);
        auto& v1 = _game.GetRegistry().emplace<Engine::Physics::Components::VelocityComponent>(rightPaddleEntity);
        auto& b1 = _game.GetRegistry().emplace<Engine::Collision::Components::BoundingBoxComponent>(rightPaddleEntity);
        auto& rightPaddleBase = _game.GetRegistry().emplace<Engine::Global::Components::BaseComponent<Game::Generated::EntityType>>(rightPaddleEntity);
        rightPaddleBase.entityType = Game::Generated::EntityType::Paddle;

        p1.attached = entt::null;
        p1.maxAcceleration = glm::vec2(0.0f, 50.0f);
        p1.velocityCeiling = glm::vec2(0.0f, 50.0f);
        v1.velocity.x = 0.0f;
        v1.velocity.y = 0.0f;
        b1.height = 60;
        b1.width = 10;
        s1.position.x = _game.GetWindow().WindowDimensions().x - 20;
        s1.position.y = 300.0f;

        glm::mat4 trans1 = glm::translate(glm::mat4(1.0f), glm::vec3(s1.position, 0.0f));
        
        s1.transform = glm::translate(trans1, glm::vec3(s1.position, 0.0f));
        
        auto& shader  = _game.GetShaderManager().GetShader(Engine::Rendering::ShaderManager::DYNAMIC_SHADER_NAME);

        d1 = Engine::Rendering::SetupDynamic(0, shader.ShaderId(), b1.width, b1.height);
    }

    void TestScene::CreateBall()
    {
        auto entity3 = _game.GetRegistry().create();

        auto& d2 = _game.GetRegistry().emplace<Engine::Rendering::Components::RenderableComponent>(entity3);
        auto& s2 = _game.GetRegistry().emplace<Engine::Global::Components::TransformComponent>(entity3);
        auto& v2 = _game.GetRegistry().emplace<Engine::Physics::Components::VelocityComponent>(entity3);
        auto& b2 = _game.GetRegistry().emplace<Engine::Collision::Components::BoundingBoxComponent>(entity3);
        auto& ball2 = _game.GetRegistry().emplace<Game::Components::BallComponent>(entity3);
        auto& ballbase = _game.GetRegistry().emplace<Engine::Global::Components::BaseComponent<Game::Generated::EntityType>>(entity3);
        ballbase.entityType = Game::Generated::EntityType::Ball;
        
        ball2.ballState = Game::Components::BallState::Attached;
        v2.velocity.x = 0.0f;
        v2.velocity.y = 0.0f;
        b2.height = 8.0f;
        b2.width = 8.0f;

        glm::mat4 trans2 = glm::mat4(1.0f);
        s2.transform = glm::translate(trans2, glm::vec3(s2.position, 0.0f));

        auto& shader  = _game.GetShaderManager().GetShader(Engine::Rendering::ShaderManager::DYNAMIC_SHADER_NAME);
        d2 = Engine::Rendering::SetupDynamic(0, shader.ShaderId(), b2.width, b2.height);
    }

    void TestScene::CreateBlocks()
    {
        auto& staticShader  = _game.GetShaderManager().GetShader(Engine::Rendering::ShaderManager::STATIC_SHADER_NAME);
        auto& debugShader  = _game.GetShaderManager().GetShader(Engine::Rendering::ShaderManager::DEBUG_SHADER_NAME);

        int width = 5;
        int height = 50;

        //render entity for static quads
        auto entity2 = _game.GetRegistry().create();
        auto& staticEntity = _game.GetRegistry().emplace<Engine::Rendering::Components::StaticRenderableComponent>(entity2);
        std::vector<glm::mat4> translations;

        float startX = 375.0f;
        float startY = 150.0f;

        float yOff = 20.0f;
        bool isYOff = false;

        std::srand(std::time(nullptr));
        
        for (int i = 1; i <= 100; ++i)
        {
            auto blockEntity = _game.GetRegistry().create();
            auto& dynDebug = _game.GetRegistry().emplace<Engine::Rendering::Components::DebugRenderableComponent>(blockEntity);
            dynDebug = Engine::Rendering::SetupDebug(debugShader.ShaderId(), width, height);

            auto& staticQuad = _game.GetRegistry().emplace<Engine::Rendering::Components::InstancedQuadComponent>(blockEntity);
            staticQuad.ignore = false;

            auto& state = _game.GetRegistry().emplace<Engine::Global::Components::EntityStateComponent>(blockEntity);
            state.active = true;

            auto& base = _game.GetRegistry().emplace<Engine::Global::Components::BaseComponent<Game::Generated::EntityType>>(blockEntity);
            base.entityType = Game::Generated::EntityType::Block;

            auto& boundingBox = _game.GetRegistry().emplace<Engine::Collision::Components::BoundingBoxComponent>(blockEntity);

            boundingBox.width = width;
            boundingBox.height = height;
            startX += 5 + 17.5f + 1 + std::rand()/((RAND_MAX + 1u)/6);
            int t = 1 + std::rand()/((RAND_MAX + 1u)/10);
            startY += isYOff ? -yOff + -1*t : yOff + t;
            isYOff = !isYOff;
            if (i % 45 == 0)
            {
                startY += 200.0f + 10;
                startX = 375.0f;
            }
            auto& pos = _game.GetRegistry().emplace<Engine::Global::Components::TransformComponent>(blockEntity);
            pos.position = glm::vec2(startX, startY);
            translations.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(startX, startY, 0.0f)));

            auto& block = _game.GetRegistry().emplace<Game::Components::BlockComponent>(blockEntity);
            block.blockState = Components::BlockState::Live;
        }

        staticEntity = Engine::Rendering::SetupStatic(0, staticShader.ShaderId(), translations, 5, 50);
    }
};