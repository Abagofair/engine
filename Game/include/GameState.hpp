#pragma once

#include "Generated/EntityType.hpp"
#include "entt/entt.hpp"

#include "Global/Time/Time.hpp"
#include "Global/Game.hpp"

namespace Game
{
    class GameState
    {
    public:
        explicit GameState(Engine::Global::Game::Game<Game::Generated::EntityType> &game);
        virtual ~GameState() = default;

        virtual void Entering() = 0;
        virtual void Leaving() = 0;

        virtual void Update(Engine::Global::Time::Time time) = 0;
        virtual void Draw() = 0;

    protected:
        Engine::Global::Game::Game<Game::Generated::EntityType> &_game;

    };
};