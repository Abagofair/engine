#include "InputManager.hpp"

namespace Engine::Input
{
    void InputManager::InitializeActionsFromDisk(
            const std::vector<Engine::Input::Action<Engine::Input::GamepadEvent>> &gamepadActions,
            const std::vector<Engine::Input::Action<Engine::Input::KeyEvent>> &keyboardActions)
    {
        _keyboardContext = nullptr;
        _gamepadContext = nullptr;

        _gamepadContext = std::unique_ptr<Input::InputContext>(
                _contextParser.CreateGamepadContext("data/Input.ini", gamepadActions));
        _keyboardContext = std::unique_ptr<Input::InputContext>(
                _contextParser.CreateKeyboardContext("data/Input.ini", keyboardActions));

        _currentContext = _keyboardContext.get();
    }

    void InputManager::HandleInput(Global::Time::Time time)
    {
        auto contextType = _currentContext->ActiveContextType();
        if (contextType != _currentContextType)
        {
            if (contextType == Input::ContextType::Gamepad &&
                CheckForGamepad())
            {
                SetContextType(Input::ContextType::Gamepad);
            }
            else
            {
                SetContextType(Input::ContextType::Keyboard);
            }
        }
        else if (_currentContextType == contextType &&
                 _elapsedTimeSinceLastCheck >= _whenToCheckForNewInputSources)
        {
            if (CheckForGamepad())
                SetContextType(Input::ContextType::Gamepad);

            _elapsedTimeSinceLastCheck = 0.0f;
        }
        _elapsedTimeSinceLastCheck += time.SecElapsedFrame;

        if (_currentContextType == ContextType::Gamepad)
            _currentContext->HandleGamepad();
        else if (_currentContextType == ContextType::Keyboard)
            _currentContext->HandleKeyboard();
    }

    void InputManager::SetContextType(Input::ContextType contextType)
    {
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

        _currentContextType = contextType;
    }

    bool InputManager::CheckForGamepad()
    {
        //todo: support more than 1 controller
        if (_controller != nullptr) return true;

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