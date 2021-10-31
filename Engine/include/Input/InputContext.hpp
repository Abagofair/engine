#pragma once

#include <functional>
#include <unordered_map>

#include "Input/InputStructures.hpp"
#include "Input/SDLInputHandler.hpp"

namespace Engine::Input
{
    class InputContext
    {
    public:

        void HandleKeyboard();
        void HandleGamepad();

        bool ActiveContextType(Input::ContextType &contextType);

        //Subscribe functions
        void OnKeyPressed(KeyCode keyCode, std::function<void(KeyEvent)> callback);
        void OnKeyReleased(KeyCode keyCode, std::function<void(KeyEvent)> callback);

        /*void OnMouseButtonDown(KeyCode, Function);
        void OnMouseButtonUp(KeyCode, Function);

        void OnMouseMoved(KeyCode, Function);*/

        /*void OnGamePadButtonDown(KeyCode, Function);
        void OnGamePadButtonUp(KeyCode, Function);*/

        void OnGamepadEvent(KeyCode gamePadCode, std::function<void(Input::GamepadEvent)> callback);
    private:
        Input::SDLInputHandler _inputHandler;

        std::unordered_map<KeyCode, std::function<void(Input::GamepadEvent)>> _callbackByGamepadCode;
        std::unordered_map<KeyCode, std::function<void(Input::KeyEvent)>> _callbackByKeyCode;

        void DispatchGamepadEvents();
        void DispatchKeyboardEvents();
    };
};