/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <memory>

#include <filesystem>

#include <Window.hpp>
#include <RGBA.hpp>
#include <Shader.hpp>

#include <glPortableHeaders.hpp>

#include <Input/InputHandler.hpp>
#include <Systems/SpriteRender.hpp>
#include <Renderer/Renderable.hpp>
#include <entt/entt.hpp>

std::unique_ptr<Window> window;

void Inputtest(Input::GamepadEvent event)
{
	std::cout << "LEFT AXIS" << std::endl;
	std::cout << event.gamepadCode << std::endl;
	std::cout << event.normalizedAxisValue << std::endl;
}

void InputtestRight(Input::GamepadEvent event)
{
	std::cout << "RIGHT AXIS" << std::endl;
	std::cout << event.gamepadCode << std::endl;
	std::cout << event.normalizedAxisValue << std::endl;
}

int main(int argc, char* args[])
{
	window = std::make_unique<Window>(800, 600, "SHITE");

	bool exit = false;

	ShaderManager shaderManager;
	uint32_t dynamicShaderId = shaderManager.LoadShader("dynamicSprite.glsl");
	uint32_t staticShaderId = shaderManager.LoadShader("staticSprite.glsl");

	entt::registry registry;
	auto entity = registry.create();
	auto& dynamic = registry.emplace<Renderables::Dynamic>(entity);
	auto& transform = registry.emplace<Components::TransformComponent>(entity);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(100.0f, 25.0f, 0.0f));
	transform = trans;
	//trans = glm::scale(trans, glm::vec3(50.0f, 50.0f, 0.0f));
	dynamic = Renderables::SetupDynamic(dynamicShaderId, 50, 15);

	entity = registry.create();
	auto& staticEntity = registry.emplace<Renderables::Static>(entity);
	auto transforms =
	{
		glm::translate(trans, glm::vec3(200.0f, 100.0f, 0.0f)),
		glm::translate(trans, glm::vec3(600.0f, 400.0f, 0.0f))
	};

	staticEntity = Renderables::SetupStatic(staticShaderId, transforms, 50, 15);

	SpriteRender spriteRender(800, 600, shaderManager);
	SDL_GameController *controller = NULL;
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

	Input::InputHandler inputHandler;
	inputHandler.OnGamepadAxisMoved(Input::GamepadCode::GamepadLeftAxis, &Inputtest);
	inputHandler.OnGamepadAxisMoved(Input::GamepadCode::GamepadRightAxis, &InputtestRight);

	while (!exit)
	{
		inputHandler.FeedEventQueue();
		inputHandler.DispatchEvents();

		auto dynamicRenderablesView = registry.view<Components::TransformComponent>();

		for (auto entity : dynamicRenderablesView)
		{
			auto& transform = dynamicRenderablesView.get<Components::TransformComponent>(entity);
			transform.transform = glm::translate(transform.transform,
				glm::vec3(0.1f, 0.0f, 0.0f));
		}

		window->ClearBuffer(RGBA(0.1f, 0.7f, 0.95f, 1.0f));
		spriteRender.Draw(registry);
		window->SwapBuffers();
	}

	return 0;
}