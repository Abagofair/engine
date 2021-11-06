#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include <iostream>

#include <RmlUi/Core.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Debugger/Debugger.h>

#include "entt/entt.hpp"

#include "Resources/ResourceHandler.hpp"

#include "Global/Game.hpp"
#include "Global/Components.hpp"
#include "GUI/RenderInterface.hpp"
#include "GUI/SystemInterface.hpp"
#include "Input/InputContextParser.hpp"

#include "Block.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Generated/EntityType.hpp"
#include "TestScene.hpp"

namespace Game
{
    class PaddleGame : public Engine::Global::Game::Game<Game::Generated::EntityType>
    {
    public:
        PaddleGame(uint32_t width, uint32_t height);

        std::vector<entt::entity> FindEntities(Generated::EntityType entityType) override;

        void Initialize() override;

        [[noreturn]] void Run() override;
        void SceneIsComplete() override;
    private:
        Paddle _paddles;
        Block _block;
        Ball _ball;

        void PauseMenu(Engine::Input::KeyEvent);
    };
};