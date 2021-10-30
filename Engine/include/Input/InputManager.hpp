#pragma once

#include <exception>
#include <memory>
#include <vector>
#include <iostream>
#include <SDL.h>

#include "InputContext.hpp"
#include "InputContextParser.hpp"
#include "Time.hpp"

#include "Logger.hpp"

namespace Engine::Input
{
    class InputManager
    {
    public:
        InputManager(const Global::Utilities::Logger& logger);

        void HandleInput(Global::Time::Time time);
        void InitializeActionsFromDisk(const std::vector<Engine::Input::Action<Engine::Input::GamepadEvent>>& gamepadActions,
                                       const std::vector<Engine::Input::Action<Engine::Input::KeyEvent>>& keyboardActions);
    private:
        const Global::Utilities::Logger& _logger;

        //seconds
        Input::ContextType _currentContextType;
        static constexpr float _whenToCheckForNewInputSources = 1.0f;
        float _elapsedTimeSinceLastCheck;

        Input::InputContextParser _contextParser;
        Input::InputContext* _currentContext;

        std::unique_ptr<Input::InputContext> _keyboardContext;
        std::unique_ptr<Input::InputContext> _gamepadContext;

        SDL_GameController* _controller = nullptr;

        void SetContextType(Input::ContextType contextType);
        bool CheckForGamepad();
    };
};