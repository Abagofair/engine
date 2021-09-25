/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <memory>

#include <filesystem>

#include <functional>

#include <External/entt/entt.hpp>

#include <Engine/Global/Utilities/RGBA.hpp>
#include <Engine/Global/Time/Time.hpp>
#include <Engine/Global/glPortableHeaders.hpp>
#include <Engine/Input/InputHandler.hpp>
#include <Engine/Windowing/Window.hpp>
#include <Engine/Rendering/Renderable.hpp>
#include <Engine/Rendering/SpriteRender.hpp>
#include <Engine/Rendering/Shader.hpp>
#include <Engine/Physics/IntegrationSystem.hpp>
#include <Engine/Collision/CollisionSystem.hpp>

#include <Game/Ball.hpp>
#include <Game/Paddle.hpp>

#include <cstdlib>
#include <ctime>

std::unique_ptr<Engine::Windowing::Window> window;

int main(int argc, char* args[])
{
	window = std::make_unique<Engine::Windowing::Window>(1920, 1080, "SHITE");

	bool exit = false;

	Engine::Rendering::ShaderManager shaderManager;
	uint32_t dynamicShaderId = shaderManager.LoadShader("dynamicSprite.glsl");
	uint32_t staticShaderId = shaderManager.LoadShader("staticSprite.glsl");
	uint32_t debugShaderId = shaderManager.LoadShader("debug.glsl");

	entt::registry registry;
	auto viewportEntity = registry.create();
	auto& viewportBase = registry.emplace<Engine::Global::Components::BaseComponent>(viewportEntity);
	auto& viewportBB = registry.emplace<Engine::Collision::Components::BoundingBoxComponent>(viewportEntity);
	auto& viewportTran = registry.emplace<Engine::Global::Components::TransformComponent>(viewportEntity);

	viewportBase.entityType = Engine::Global::Generated::EntityType::ViewportContainer;
	viewportBB.contains = true;
	viewportBB.width = 1920;
	viewportBB.height = 1080;

	viewportTran.position = glm::vec3(0.0);
	viewportTran.transform = glm::mat4(1.0f);

	auto entity = registry.create();
	auto& d = registry.emplace<Engine::Rendering::Renderable::Dynamic>(entity);
	auto& p = registry.emplace<Game::Components::LeftPaddleComponent>(entity);
	auto& s = registry.emplace<Engine::Global::Components::TransformComponent>(entity);
	auto& v = registry.emplace<Engine::Physics::Components::VelocityComponent>(entity);
	auto& b = registry.emplace<Engine::Collision::Components::BoundingBoxComponent>(entity);
	
	p.maxAcceleration = glm::vec2(0.0f, 50.0f);
	p.velocityCeiling = glm::vec2(0.0f, 100.0f);
	v.velocity.x = 0.0f;
	v.velocity.y = 0.0f;
	b.height = 60;
	b.width = 10;
	s.position.x = 10.0f;
	s.position.y = 0.0f;
	s.recalculateTransform = false;

	glm::mat4 trans = glm::mat4(1.0f);
	s.transform = glm::translate(glm::mat4(1.0f), glm::vec3(s.position, 0.0f));
	s.transform = glm::scale(s.transform, glm::vec3(10.0f, 60.0f, 0.0f));
	d = Engine::Rendering::Renderable::SetupDynamic(dynamicShaderId, b.width, b.height);

	auto entity1 = registry.create();
	auto& d1 = registry.emplace<Engine::Rendering::Renderable::Dynamic>(entity1);
	auto& s1 = registry.emplace<Engine::Global::Components::TransformComponent>(entity1);
	auto& p1 = registry.emplace<Game::Components::RightPaddleComponent>(entity1);
	auto& v1 = registry.emplace<Engine::Physics::Components::VelocityComponent>(entity1);
	auto& b1 = registry.emplace<Engine::Collision::Components::BoundingBoxComponent>(entity1);
	
	p1.attached = entt::null;
	p1.maxAcceleration = glm::vec2(0.0f, 50.0f);
	p1.velocityCeiling = glm::vec2(0.0f, 100.0f);
	v1.velocity.x = 0.0f;
	v1.velocity.y = 0.0f;
	b1.height = 60;
	b1.width = 10;
	s1.position.x = window->WindowDimensions().x - 20;
	s1.position.y = 300.0f;

	glm::mat4 trans1 = glm::translate(glm::mat4(1.0f), glm::vec3(s1.position, 0.0f));
	
	s1.transform = glm::translate(trans1, glm::vec3(s1.position, 0.0f));
	d1 = Engine::Rendering::Renderable::SetupDynamic(dynamicShaderId, b1.width, b1.height);

	auto entity3 = registry.create();
	
	p.attached = entity3;

	auto& d2 = registry.emplace<Engine::Rendering::Renderable::Dynamic>(entity3);
	auto& s2 = registry.emplace<Engine::Global::Components::TransformComponent>(entity3);
	auto& v2 = registry.emplace<Engine::Physics::Components::VelocityComponent>(entity3);
	auto& b2 = registry.emplace<Engine::Collision::Components::BoundingBoxComponent>(entity3);
	auto& ball2 = registry.emplace<Game::Components::BallComponent>(entity3);
	auto& ballbase = registry.emplace<Engine::Global::Components::BaseComponent>(entity3);
	ballbase.entityType = Engine::Global::Generated::EntityType::Ball;
	
	ball2.ballState = Game::Components::BallState::Attached;
	v2.velocity.x = 0.0f;
	v2.velocity.y = 0.0f;
	b2.height = 6.0f;
	b2.width = 6.0f;
	s2.position.x = s.position.x + 20.0f;
	s2.position.y = s.position.y;

	glm::mat4 trans2 = glm::mat4(1.0f);
	s2.transform = glm::translate(trans2, glm::vec3(s2.position, 0.0f));
	d2 = Engine::Rendering::Renderable::SetupDynamic(dynamicShaderId, b2.width, b2.height);

	//render entity for static quads
	auto entity2 = registry.create();
	auto& staticEntity = registry.emplace<Engine::Rendering::Renderable::Static>(entity2);
	std::vector<glm::mat4> translations;

	float startX = 375.0f;
	float startY = 150.0f;

	float yOff = 20.0f;
	bool isYOff = false;

	std::srand(std::time(nullptr));
	
	for (int i = 1; i <= 245; ++i)
	{
		auto blockEntity = registry.create();
		auto& dynDebug = registry.emplace<Engine::Rendering::Renderable::Dynamic>(blockEntity);
		auto& base = registry.emplace<Engine::Global::Components::BaseComponent>(blockEntity);
		base.entityType = Engine::Global::Generated::EntityType::Block;
		dynDebug = Engine::Rendering::Renderable::SetupDynamic(debugShaderId, 5, 50);
		auto& boundingBox = registry.emplace<Engine::Collision::Components::BoundingBoxComponent>(blockEntity);
		boundingBox.width = b1.width;
		boundingBox.height = b1.height;
		startX += 5 + 17.5f + 1 + std::rand()/((RAND_MAX + 1u)/6);
		int t = 1 + std::rand()/((RAND_MAX + 1u)/10);
		startY += isYOff ? -yOff + -1*t : yOff + t;
		isYOff = !isYOff;
		if (i % 45 == 0)
		{
			startY += 150.0f + 10;
			startX = 375.0f;
		}
		auto& pos = registry.emplace<Engine::Global::Components::TransformComponent>(blockEntity);
		pos.position = glm::vec2(startX, startY);
		translations.push_back(glm::translate(trans, glm::vec3(startX, startY, 0.0f))); 
	}

	staticEntity = Engine::Rendering::Renderable::SetupStatic(staticShaderId, translations, 5, 50);

	Engine::Rendering::SpriteRender spriteRender(1920, 1080, shaderManager);

	Game::Paddle playerSystem(registry);
	//playerSystem.SetPosition(glm::uvec2(100, 300));
	Game::Ball ballSystem(registry);
	
	Engine::Physics::IntegrationSystem integrationSystem(registry);
	Engine::Collision::CollisionSystem collisionSystem(registry);

	//for entity ball on collision with block do velocity reflection as defined by some handler
	collisionSystem.AddCollisionHandler(entity3,
			Engine::Global::Generated::EntityType::Block,
			std::bind(&Game::Ball::OnBlockCollision, &ballSystem, std::placeholders::_1));
	collisionSystem.AddCollisionHandler(entity3,
			Engine::Global::Generated::EntityType::ViewportContainer,
			std::bind(&Game::Ball::OnViewportCollision, &ballSystem, std::placeholders::_1));

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

	Engine::Input::InputHandler inputHandler;
	inputHandler.OnGamepadEvent(Engine::Input::GamepadCode::GamepadLeftAxis, std::bind(&Game::Paddle::MoveLeft, &playerSystem, std::placeholders::_1));
	inputHandler.OnGamepadEvent(Engine::Input::GamepadCode::GamepadRightAxis, std::bind(&Game::Paddle::MoveRight, &playerSystem, std::placeholders::_1));
	inputHandler.OnGamepadEvent(Engine::Input::GamepadCode::GamepadButtonA, std::bind(&Game::Paddle::LaunchBall, &playerSystem, std::placeholders::_1));
	inputHandler.OnGamepadEvent(Engine::Input::GamepadCode::GamepadButtonB, std::bind(&Game::Paddle::DebugAttachBall, &playerSystem, std::placeholders::_1));

	uint32_t previousTime = SDL_GetTicks();

	while (!exit)
	{
		auto dynamicRenderablesView = registry.view<
			Engine::Global::Components::TransformComponent>();

		Engine::Global::Time::Time time;
		time.MsElapsedTotal = SDL_GetTicks();
		time.MsElapsedFrame = time.MsElapsedTotal - previousTime;
		previousTime = time.MsElapsedTotal;
		time.SecElapsedFrame = time.MsElapsedFrame / 1000.0f;

		inputHandler.FeedEventQueue();
		inputHandler.DispatchEvents();
		playerSystem.Update();
		ballSystem.Update();
		integrationSystem.Integrate(time);
		collisionSystem.Handle();

		for (auto entity : dynamicRenderablesView)
		{
			auto& transform = dynamicRenderablesView.get<Engine::Global::Components::TransformComponent>(entity);
			//if (sprite.recalculateTransform)
			transform.transform = glm::translate(glm::mat4(1.0f), glm::vec3(transform.position, 0.0f));
			//transform.transform = glm::scale(transform.transform, glm::vec3(10.0f, 60.0f, 0.0f));
		}

		window->ClearBuffer(Engine::Global::Utilities::RGBA(0.1f, 0.7f, 0.95f, 1.0f));
		spriteRender.Draw(registry);
		window->SwapBuffers();
	}

	return 0;
}