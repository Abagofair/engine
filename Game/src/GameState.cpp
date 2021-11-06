#include "GameState.hpp"

namespace Game
{

    GameState::GameState(Engine::Global::Game::Game<Game::Generated::EntityType> &game)
        : _game(game)
    {}
};