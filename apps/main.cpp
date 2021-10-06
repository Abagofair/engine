//Using SDL and standard IO
#include <SDL.h>

#include <iostream>
#include <memory>

#include <PaddleGame.hpp>

int main(int argc, char* args[])
{
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