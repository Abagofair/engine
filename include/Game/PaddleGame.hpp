#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include <External/entt/entt.hpp>

#include <Engine/Global/Game.hpp>
#include <Engine/Global/Components.hpp>

#include <Game/Block.hpp>
#include <Game/Ball.hpp>
#include <Game/Paddle.hpp>
#include <Game/Generated/EntityType.hpp>
#include <Game/TestScene.hpp>

namespace Game
{
    class PaddleGame : public Engine::Global::Game::Game<Game::Generated::EntityType>
    {
    public:
        PaddleGame(uint32_t width, uint32_t height);

        std::vector<entt::entity> FindEntities(Generated::EntityType entityType) override;

        void Initialize() override;
        void Run() override;
    private:
        Paddle _paddles;
        Block _block;
        Ball _ball;
    };
};