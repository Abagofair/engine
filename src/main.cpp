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
#include <Systems/CollisionSystem.hpp>

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
	auto& p = registry.emplace<Components::LeftPaddleComponent>(entity);
	auto& s = registry.emplace<Components::SpriteComponent>(entity);
	auto& v = registry.emplace<Components::VelocityComponent>(entity);
	auto& b = registry.emplace<Components::BoundingBoxComponent>(entity);
	
	p.maxAcceleration = glm::vec2(0.0f, 100.5f);
	p.velocityCeiling = glm::vec2(0.0f, 200.0f);
	v.velocity.x = 0.0f;
	v.velocity.y = 0.0f;
	p.isLeft = true;
	b.height = 30;
	b.width = 10;
	s.position.x = 30.0f;
	s.position.y = 300.0f;

	glm::mat4 trans = glm::mat4(1.0f);
	t = glm::translate(trans, glm::vec3(s.position, 0.0f));
	d = Renderables::SetupDynamic(dynamicShaderId, b.width, b.height);

	auto entity1 = registry.create();
	auto& d1 = registry.emplace<Renderables::Dynamic>(entity1);
	auto& t1 = registry.emplace<Components::TransformComponent>(entity1);
	auto& p1 = registry.emplace<Components::RightPaddleComponent>(entity1);
	auto& s1 = registry.emplace<Components::SpriteComponent>(entity1);
	auto& v1 = registry.emplace<Components::VelocityComponent>(entity1);
	auto& b1 = registry.emplace<Components::BoundingBoxComponent>(entity1);
	
	p1.maxAcceleration = glm::vec2(0.0f, 100.5f);
	p1.velocityCeiling = glm::vec2(0.0f, 200.0f);
	v1.velocity.x = 0.0f;
	v1.velocity.y = 0.0f;
	p1.isLeft = true;
	b1.height = 30;
	b1.width = 10;
	s1.position.x = 770.0f;
	s1.position.y = 300.0f;

	glm::mat4 trans1 = glm::mat4(1.0f);
	t1 = glm::translate(trans1, glm::vec3(s1.position, 0.0f));
	d1 = Renderables::SetupDynamic(dynamicShaderId, b1.width, b1.height);

	auto entity2 = registry.create();
	auto& staticEntity = registry.emplace<Renderables::Static>(entity2);
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
	CollisionSystem collisionSystem(registry, *window);

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
	inputHandler.OnGamepadAxisMoved(Input::GamepadCode::GamepadLeftAxis, std::bind(&PlayerSystem::MoveLeft, &playerSystem, std::placeholders::_1));
	inputHandler.OnGamepadAxisMoved(Input::GamepadCode::GamepadRightAxis, std::bind(&PlayerSystem::MoveRight, &playerSystem, std::placeholders::_1));

	uint32_t previousTime = SDL_GetTicks();

	while (!exit)
	{
		auto dynamicRenderablesView = registry.view<
			Components::TransformComponent, 
			Components::SpriteComponent>();

		InternalTime::Time time;
		time.MsElapsedTotal = SDL_GetTicks();
		time.MsElapsedFrame = time.MsElapsedTotal - previousTime;
		previousTime = time.MsElapsedTotal;
		time.SecElapsedFrame = time.MsElapsedFrame / 1000.0f;

		inputHandler.FeedEventQueue();
		inputHandler.DispatchEvents();

		playerSystem.Update();

		integrationSystem.Integrate(time);

		collisionSystem.ResolveVelocities();

		for (auto entity : dynamicRenderablesView)
		{
			auto sprite = dynamicRenderablesView.get<Components::SpriteComponent>(entity);
			auto& transform = dynamicRenderablesView.get<Components::TransformComponent>(entity);
			if (sprite.recalculateTransform)
				transform.transform = glm::translate(glm::mat4(1.0f), glm::vec3(sprite.position, 0.0f));
		}

		window->ClearBuffer(RGBA(0.1f, 0.7f, 0.95f, 1.0f));
		spriteRender.Draw(registry);
		window->SwapBuffers();
	}

	return 0;
}