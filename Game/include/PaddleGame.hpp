#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "External/include/entt/entt.hpp"

#include "Engine/include/Global/Game.hpp"
#include "Engine/include/Global/Components.hpp"

#include "Block.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Generated/EntityType.hpp"
#include "TestScene.hpp"

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