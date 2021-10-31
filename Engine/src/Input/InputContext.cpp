#include "Input/InputContext.hpp"

namespace Engine::Input
{
    void InputContext::OnGamepadEvent(Input::KeyCode gamePadCode, std::function<void(Input::GamepadEvent)> callback)
    {
        _callbackByGamepadCode[gamePadCode] = std::move(callback);
    }

    void InputContext::OnKeyPressed(KeyCode keyCode, std::function<void(KeyEvent)> callback)
    {
        _callbackByKeyCode[keyCode] = std::move(callback);
    }

    void InputContext::OnKeyReleased(KeyCode keyCode, std::function<void(KeyEvent)> callback)
    {
        _callbackByKeyCode[keyCode] = std::move(callback);
    }

    void InputContext::HandleKeyboard()
    {
        _inputHandler.FeedEventQueue();
        DispatchKeyboardEvents();
    }

    void InputContext::HandleGamepad()
    {
        _inputHandler.FeedEventQueue();
        DispatchGamepadEvents();
    }

    void InputContext::DispatchGamepadEvents()
    {
        Input::GamepadEvent gamepadEvent;
        while (_inputHandler.GetNextGamepadEvent(gamepadEvent))
        {
            auto callback = _callbackByGamepadCode.find(gamepadEvent.gamepadCode);
            if (callback != _callbackByGamepadCode.end())
            {
                callback->second(gamepadEvent);
            }
        }
    }

    void InputContext::DispatchKeyboardEvents()
    {
        Input::KeyEvent keyEvent;
        while (_inputHandler.GetNextKeyEvent(keyEvent))
        {
            auto callback = _callbackByKeyCode.find(keyEvent.keyCode);
            if (callback != _callbackByKeyCode.end())
            {
                callback->second(keyEvent);
            }
        }
    }

    bool InputContext::ActiveContextType(Input::ContextType &contextType)
    {
        return _inputHandler.GetFirstActiveInputSource(contextType);
    }
};