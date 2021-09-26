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

#include <Engine/Rendering/ShaderManager.hpp>
#include <Engine/Rendering/Shader.hpp>

#include <Game/Generated/EntityType.hpp>
#include <Game/Ball.hpp>
#include <Game/Paddle.hpp>
#include <Game/PaddleGame.hpp>
#include <Game/TestScene.hpp>

#include <cstdlib>
#include <ctime>

int main(int argc, char* args[])
{
	bool exit = false;

	Engine::Rendering::ShaderManager shaderManager;
	shaderManager.LoadShader("dynamicSprite.glsl", Engine::Rendering::DYNAMIC_SHADER_NAME);
	shaderManager.LoadShader("staticSprite.glsl", Engine::Rendering::STATIC_SHADER_NAME);
	shaderManager.LoadShader("debug.glsl", Engine::Rendering::DEBUG_SHADER_NAME);

	Game::PaddleGame paddleGame(1920, 1080);
	paddleGame.Initialize();

	//for entity ball on collision with block do velocity reflection as defined by some handler
	/*collisionSystem.AddCollisionCallback(entity3,
		Game::Generated::EntityType::Block,
		std::bind(&Game::Ball::OnBlockCollision, &ballSystem, std::placeholders::_1));
	collisionSystem.AddCollisionCallback(entity3,
		Game::Generated::EntityType::Paddle,
		std::bind(&Game::Ball::OnBlockCollision, &ballSystem, std::placeholders::_1));
	collisionSystem.AddCollisionCallback(entity3,
		Game::Generated::EntityType::ViewportContainer,
		std::bind(&Game::Ball::OnViewportCollision, &ballSystem, std::placeholders::_1));

	collisionSystem.AddCollisionCallback(leftPaddleEntity,
		Game::Generated::EntityType::ViewportContainer,
		std::bind(&Game::Paddle::OnViewportCollision, &playerSystem, std::placeholders::_1));
	collisionSystem.AddCollisionCallback(rightPaddleEntity,
		Game::Generated::EntityType::ViewportContainer,
		std::bind(&Game::Paddle::OnViewportCollision, &playerSystem, std::placeholders::_1));*/

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

	/*Engine::Input::InputHandler inputHandler;
	inputHandler.OnGamepadEvent(Engine::Input::GamepadCode::GamepadLeftAxis, std::bind(&Game::Paddle::MoveLeft, &playerSystem, std::placeholders::_1));
	inputHandler.OnGamepadEvent(Engine::Input::GamepadCode::GamepadRightAxis, std::bind(&Game::Paddle::MoveRight, &playerSystem, std::placeholders::_1));
	inputHandler.OnGamepadEvent(Engine::Input::GamepadCode::GamepadButtonA, std::bind(&Game::Paddle::LaunchBall, &playerSystem, std::placeholders::_1));
	inputHandler.OnGamepadEvent(Engine::Input::GamepadCode::GamepadButtonB, std::bind(&Game::Paddle::DebugAttachBall, &playerSystem, std::placeholders::_1));*/

	uint32_t previousTime = SDL_GetTicks();

	/*while (!exit)
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
		collisionSystem.BroadPhase();

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
	}*/

	return 0;
}