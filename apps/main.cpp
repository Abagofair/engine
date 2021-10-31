//Using SDL and standard IO
#include <PaddleGame.hpp>

int main(int argc, char* args[])
{
    Game::PaddleGame paddleGame(1920, 1080);

    paddleGame.Initialize();
    paddleGame.Run();
}