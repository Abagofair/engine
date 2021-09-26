#pragma once

#include <cstdint>

#include <Engine/Global/Game.hpp>

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

        void Initialize();
        void Run();
    private:
        Paddle _paddles;
        Ball _ball;
    };
};