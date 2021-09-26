#include <Game/PaddleGame.hpp>

namespace Game
{
    PaddleGame::PaddleGame(uint32_t width, uint32_t height)
        : Game(width, height), _paddles(_registry), _ball(_registry)
    {
    }

    void PaddleGame::Initialize()
    {
        _currentScene = TestScene(*this);
    }

    void PaddleGame::Run()
    {

    }
};