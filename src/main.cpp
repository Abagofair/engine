/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <memory>

#include <Window.hpp>
#include <RGBA.hpp>

#include <glPortableHeaders.hpp>

std::unique_ptr<Window> window;

int main(int argc, char* args[])
{
	window = std::make_unique<Window>(800, 600, "SHITE");

	bool exit = false;

	while (!exit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					exit = true;
				}
				break;
			default:
				break;
			}
		}

		window->ClearBuffer(RGBA(0.1f, 0.7f, 0.95f, 1.0f));

		/*glUseProgram(shaderProgram);
		texture->Bind();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);*/

		window->SwapBuffers();
	}

	return 0;
}