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
#include <Systems/BallSystem.hpp>
#include <Systems/IntegrationSystem.hpp>
#include <Systems/CollisionSystem.hpp>

#include <Renderer/Renderable.hpp>
#include <entt/entt.hpp>

#include <Time.hpp>

#include <cstdlib>
#include <ctime>

std::unique_ptr<Window> window;

int main(int argc, char* args[])
{
	window = std::make_unique<Window>(1920, 1080, "SHITE");

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
	
	p.maxAcceleration = glm::vec2(0.0f, 50.0f);
	p.velocityCeiling = glm::vec2(0.0f, 100.0f);
	v.velocity.x = 0.0f;
	v.velocity.y = 0.0f;
	b.height = 60;
	b.width = 10;
	s.position.x = 20.0f;
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
	
	p1.attached = entt::null;
	p1.maxAcceleration = glm::vec2(0.0f, 50.0f);
	p1.velocityCeiling = glm::vec2(0.0f, 100.0f);
	v1.velocity.x = 0.0f;
	v1.velocity.y = 0.0f;
	b1.height = 60;
	b1.width = 10;
	s1.position.x = window->WindowDimensions().x - 20;
	s1.position.y = 300.0f;

	glm::mat4 trans1 = glm::mat4(1.0f);
	t1 = glm::translate(trans1, glm::vec3(s1.position, 0.0f));
	d1 = Renderables::SetupDynamic(dynamicShaderId, b1.width, b1.height);

	auto entity3 = registry.create();
	
	p.attached = entity3;

	auto& d2 = registry.emplace<Renderables::Dynamic>(entity3);
	auto& t2 = registry.emplace<Components::TransformComponent>(entity3);
	auto& s2 = registry.emplace<Components::SpriteComponent>(entity3);
	auto& v2 = registry.emplace<Components::VelocityComponent>(entity3);
	auto& b2 = registry.emplace<Components::BoundingBoxComponent>(entity3);
	auto& ball2 = registry.emplace<Components::BallComponent>(entity3);
	
	ball2.ballState = Components::BallState::Attached;
	v2.velocity.x = 0.0f;
	v2.velocity.y = 0.0f;
	b2.height = 7.5f;
	b2.width = 7.5f;
	s2.position.x = s.position.x + 20.0f;
	s2.position.y = s.position.y;

	glm::mat4 trans2 = glm::mat4(1.0f);
	t2 = glm::translate(trans2, glm::vec3(s2.position, 0.0f));
	d2 = Renderables::SetupDynamic(dynamicShaderId, b2.width, b2.height);

	//render entity for static quads
	auto entity2 = registry.create();
	auto& staticEntity = registry.emplace<Renderables::Static>(entity2);
	std::vector<glm::mat4> translations;

	float startX = 375.0f;
	float startY = 150.0f;

	float yOff = 20.0f;
	bool isYOff = false;

	std::srand(std::time(nullptr));

	for (int i = 1; i <= 245; ++i)
	{
		auto blockEntity = registry.create();
		auto& boundingBox = registry.emplace<Components::BoundingBoxComponent>(blockEntity);
		startX += 5 + 17.5f + 1 + std::rand()/((RAND_MAX + 1u)/6);
		int t = 1 + std::rand()/((RAND_MAX + 1u)/10);
		startY += isYOff ? -yOff + -1*t : yOff + t;
		isYOff = !isYOff;
		if (i % 45 == 0)
		{
			startY += 150.0f + 10;
			startX = 375.0f;
		}
		translations.push_back(glm::translate(trans, glm::vec3(startX, startY, 0.0f))); 
	}

	staticEntity = Renderables::SetupStatic(staticShaderId, translations, 5, 50);

	SpriteRender spriteRender(1920, 1080, shaderManager);

	PlayerSystem playerSystem(registry);
	playerSystem.SetPosition(glm::uvec2(100, 300));
	BallSystem ballSystem(registry);
	
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
	inputHandler.OnGamepadEvent(Input::GamepadCode::GamepadLeftAxis, std::bind(&PlayerSystem::MoveLeft, &playerSystem, std::placeholders::_1));
	inputHandler.OnGamepadEvent(Input::GamepadCode::GamepadRightAxis, std::bind(&PlayerSystem::MoveRight, &playerSystem, std::placeholders::_1));
	inputHandler.OnGamepadEvent(Input::GamepadCode::GamepadButton1, std::bind(&PlayerSystem::LaunchBall, &playerSystem, std::placeholders::_1));

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
		ballSystem.Update();
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