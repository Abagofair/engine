/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <memory>

#include <filesystem>

#include <functional>

#include <Window.hpp>
#include <RGBA.hpp>
#include <Shader.hpp>

#include <glPortableHeaders.hpp>

#include <Input/InputHandler.hpp>

#include <Systems/SpriteRender.hpp>
#include <Systems/PlayerSystem.hpp>
#include <Systems/IntegrationSystem.hpp>

#include <Renderer/Renderable.hpp>
#include <entt/entt.hpp>

#include <Time.hpp>

std::unique_ptr<Window> window;

int main(int argc, char* args[])
{
	window = std::make_unique<Window>(800, 600, "SHITE");

	bool exit = false;

	ShaderManager shaderManager;
	uint32_t dynamicShaderId = shaderManager.LoadShader("dynamicSprite.glsl");
	uint32_t staticShaderId = shaderManager.LoadShader("staticSprite.glsl");

	entt::registry registry;
	auto entity = registry.create();
	auto& d = registry.emplace<Renderables::Dynamic>(entity);
	auto& t = registry.emplace<Components::TransformComponent>(entity);
	auto& p = registry.emplace<Components::PaddleComponent>(entity);
	p.speed = 100.0f;
	auto& s = registry.emplace<Components::SpriteComponent>(entity);
	auto& v = registry.emplace<Components::VelocityComponent>(entity);
	v.velocity.x = 0.0f;
	v.velocity.y = 0.0f;

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(100.0f, 25.0f, 0.0f));
	t = trans;
	//trans = glm::scale(trans, glm::vec3(50.0f, 50.0f, 0.0f));
	d = Renderables::SetupDynamic(dynamicShaderId, 50, 15);

	entity = registry.create();
	auto& staticEntity = registry.emplace<Renderables::Static>(entity);
	auto transforms =
	{
		glm::translate(trans, glm::vec3(200.0f, 100.0f, 0.0f)),
		glm::translate(trans, glm::vec3(600.0f, 400.0f, 0.0f))
	};

	staticEntity = Renderables::SetupStatic(staticShaderId, transforms, 50, 15);

	SpriteRender spriteRender(800, 600, shaderManager);

	PlayerSystem playerSystem(registry);
	playerSystem.SetPosition(glm::uvec2(100, 300));
	
	IntegrationSystem integrationSystem(registry);

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
	inputHandler.OnGamepadAxisMoved(Input::GamepadCode::GamepadLeftAxis, std::bind(&PlayerSystem::Move, &playerSystem, std::placeholders::_1));

	uint32_t initialTime = SDL_GetTicks();

	while (!exit)
	{
		InternalTime::Time time;
		time.MsElapsedTotal = SDL_GetTicks();
		time.MsElapsedFrame = (time.MsElapsedTotal - initialTime);
		time.SecElapsedFrame = time.MsElapsedFrame / 1000.0f;

		inputHandler.FeedEventQueue();
		inputHandler.DispatchEvents();

		integrationSystem.Integrate(time);

		auto dynamicRenderablesView = registry.view<Components::TransformComponent, 
			Components::SpriteComponent>();

		for (auto entity : dynamicRenderablesView)
		{
			auto sprite = dynamicRenderablesView.get<Components::SpriteComponent>(entity);
			auto& transform = dynamicRenderablesView.get<Components::TransformComponent>(entity);
			transform.transform = glm::translate(transform.transform, glm::vec3(sprite.position, 0.0f));
		}

		window->ClearBuffer(RGBA(0.1f, 0.7f, 0.95f, 1.0f));
		spriteRender.Draw(registry);
		window->SwapBuffers();
	}

	return 0;
}