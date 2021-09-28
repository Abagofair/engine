//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <memory>

#include <Engine/Global/Utilities/RGBA.hpp>
#include <Engine/Global/Time/Time.hpp>
#include <Engine/Input/InputHandler.hpp>
#include <Engine/Windowing/Window.hpp>
#include <Engine/Rendering/SpriteRender.hpp>
#include <Engine/Physics/IntegrationSystem.hpp>
#include <Engine/Collision/CollisionSystem.hpp>
#include <Game/Generated/EntityType.hpp>
#include <Game/Ball.hpp>
#include <Game/Paddle.hpp>
#include <Game/PaddleGame.hpp>

int main(int argc, char* args[])
{
	bool exit = false;

    Game::PaddleGame paddleGame(1920, 1080);
    paddleGame.Initialize();

	//for entity ball on collision with block do velocity reflection as defined by some handler

	SDL_GameController *controller = nullptr;
	std::cout << SDL_NumJoysticks() << std::endl;
	std::cout << SDL_GetError() << std::endl;
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			
			std::cout << SDL_GameControllerGetType(controller) << std::endl;
			if (controller) {
				break;
			} else {
				fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}

    paddleGame.Run();

	return 0;
}