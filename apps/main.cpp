//Using SDL and standard IO
#include <PaddleGame.hpp>

int main(int argc, char* args[])
{
    Engine::Global::Utilities::Logger::SetupSink(std::cout);

    Game::PaddleGame paddleGame(1920, 1080);

    paddleGame.Initialize();
    paddleGame.Run();
}