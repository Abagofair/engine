#include "Input/InputManager.hpp"

namespace Engine::Input
{
    void InputManager::InitializeActionsFromDisk(
            const std::vector<Engine::Input::Action<Engine::Input::GamepadEvent>> &gamepadActions,
            const std::vector<Engine::Input::Action<Engine::Input::KeyEvent>> &keyboardActions)
    {
        Global::Utilities::Logger::WriteInfo("Initialized actions from disk", "");

        _keyboardContext = nullptr;
        _gamepadContext = nullptr;

        _gamepadContext = std::unique_ptr<Input::InputContext>(
                _contextParser.CreateGamepadContext("data/Input.ini", gamepadActions, _inputHandler));
        _keyboardContext = std::unique_ptr<Input::InputContext>(
                _contextParser.CreateKeyboardContext("data/Input.ini", keyboardActions, _inputHandler));

        _currentContext = _keyboardContext.get();
        SetContextType(Input::ContextType::Keyboard);
    }

    void InputManager::HandleInput(Global::Time::Time time)
    {
        if (_currentContext == nullptr)
        {
            Global::Utilities::Logger::WriteWarning("_currentContext is currently null", "");
            return;
        }

        _currentContext->FeedEventQueues();

        Input::ContextType contextType;
        bool hasEvents = _currentContext->ActiveContextType(contextType);
        if (hasEvents && contextType != _currentContextType)
        {
            std::string c = contextType == ContextType::Gamepad ? "Gamepad" : "Keyboard";
            Global::Utilities::Logger::WriteWarning("% to %", "Switching context type", c);
            SetContextType(contextType);
        }
        else if (_elapsedTimeSinceLastCheck >= _whenToCheckForNewInputSources)
        {
            if (CheckForGamepad())
            {
                Global::Utilities::Logger::WriteWarning("Connecting gamepad..", "");
                SetContextType(Input::ContextType::Gamepad);
            }

            _elapsedTimeSinceLastCheck = 0.0f;
        }
        _elapsedTimeSinceLastCheck += time.SecElapsedFrame;

        if (_currentContextType == ContextType::Gamepad)
        {
            _currentContext->HandleGamepad();
        }
        else if (_currentContextType == ContextType::Keyboard)
        {
            _currentContext->HandleKeyboard();
        }
    }

    void InputManager::SetContextType(Input::ContextType contextType)
    {
        _currentContextType = contextType;

        switch (contextType)
        {
            case Input::ContextType::Keyboard:
                _currentContext = _keyboardContext.get();
                break;
            case Input::ContextType::Gamepad:
                _currentContext = _gamepadContext.get();
                break;
            default:
                throw std::exception("Invalid input context");
        }
    }

    bool InputManager::CheckForGamepad()
    {
        //todo: support more than 1 controller
        if (_controller != nullptr) return false;

        for (int i = 0; i < SDL_NumJoysticks(); ++i)
        {
            if (SDL_IsGameController(i))
            {
                _controller = SDL_GameControllerOpen(i);

                std::cout << SDL_GameControllerGetType(_controller) << std::endl;
                if (_controller != nullptr)
                {
                    return true;
                }
                else
                {
                    fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
                }
            }
        }
        return false;
    }
};