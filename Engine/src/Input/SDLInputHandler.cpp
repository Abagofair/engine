#include "SDLInputHandler.hpp"

namespace Engine::Input
{
    void SDLInputHandler::FeedEventQueue()
    {
        SDL_Event event;

        //todo: should log if this fails
        //_gamepadEventQueue.empty();
        //_keyboardEventQueue.empty();

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_CONTROLLERAXISMOTION:
                {
                    ControllerAxisMotion(event);
                    break;
                }
                case SDL_CONTROLLERBUTTONDOWN:
                {
                    ControllerButtonDown(event);
                    break;
                }
                case SDL_QUIT:
                {
                    break;
                }
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        KeyEvent keyEvent;
                        keyEvent.keyCode = KeyCode::ESC;
                        keyEvent.inputEventType = InputEventType::KeyPressed;
                        keyEvent.priority = 1;
                        keyEvent.timestamp = event.key.timestamp;

                        _keyboardEventQueue.push(keyEvent);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    void SDLInputHandler::ControllerButtonDown(SDL_Event event)
    {
        GamepadEvent gamepadEvent{};

        gamepadEvent.inputEventType = InputEventType::GamePadButtonDown;
        if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
        {
            gamepadEvent.gamepadCode = KeyCode::GamepadA;
        }
        else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
        {
            gamepadEvent.gamepadCode = KeyCode::GamepadB;
        }
        else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
        {
            gamepadEvent.gamepadCode = KeyCode::GamePadStart;
        }

        gamepadEvent.timestamp = event.caxis.timestamp;

        _gamepadEventQueue.push(gamepadEvent);
    }

    void SDLInputHandler::ControllerAxisMotion(SDL_Event event)
    {
        GamepadEvent gamepadEvent{};

        auto axis = static_cast<SDL_GameControllerAxis>(event.caxis.axis);
        if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX)
        {
            gamepadEvent.gamepadCode = KeyCode::LeftAnalog;
            _currentLeftAxisValue.x = event.caxis.value;
            MapControllerAnalogMovement(gamepadEvent);
        }
        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY)
        {
            gamepadEvent.gamepadCode = KeyCode::LeftAnalog;
            _currentLeftAxisValue.y = event.caxis.value;
            MapControllerAnalogMovement(gamepadEvent);
        }
        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX)
        {
            gamepadEvent.gamepadCode = KeyCode::RightAnalog;
            _currentRightAxisValue.x = event.caxis.value;
            MapControllerAnalogMovement(gamepadEvent);
        }
        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY)
        {
            gamepadEvent.gamepadCode = KeyCode::RightAnalog;
            _currentRightAxisValue.y = event.caxis.value;
            MapControllerAnalogMovement(gamepadEvent);
        }
        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT)
        {
            gamepadEvent.gamepadCode = KeyCode::LeftTrigger;
            _currentLeftTriggerValue = event.caxis.value;
            MapControllerTriggerMovement(gamepadEvent);
        }
        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
        {
            gamepadEvent.gamepadCode = KeyCode::RightTrigger;
            _currentRightTriggerValue = event.caxis.value;
            MapControllerTriggerMovement(gamepadEvent);
        }

        gamepadEvent.timestamp = event.caxis.timestamp;

        _gamepadEventQueue.push(gamepadEvent);
    }

    GamepadEvent SDLInputHandler::MapControllerAnalogMovement(GamepadEvent &gamepadEvent) const
    {
        float magnitude;
        float normalizedMagnitude;

        //https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput
        //determine how far the controller is pushed
        magnitude = MagnitudeOfCurrentAnalog(gamepadEvent.gamepadCode);

        //determine the direction the controller is pushed
        gamepadEvent.normalizedAnalogDirection = NormalizeCurrentAnalogDirection(gamepadEvent.gamepadCode, magnitude);

        uint32_t axisThreshold = AxisThreshold(gamepadEvent.gamepadCode);

        if (magnitude > axisThreshold)
        {
            //clip the magnitude at its expected maximum value
            if (magnitude > MAXIMUM_AXIS_VALUE)
                magnitude = MAXIMUM_AXIS_VALUE;

            //adjust magnitude relative to the end of the dead zone
            magnitude -= axisThreshold;

            //optionally normalize the magnitude with respect to its expected range
            //giving a magnitude value of 0.0 to 1.0
            normalizedMagnitude = magnitude / (MAXIMUM_AXIS_VALUE - axisThreshold);
        }
        else //if the controller is in the deadzone zero out the magnitude
        {
            normalizedMagnitude = 0.0;
        }

        if (gamepadEvent.normalizedAnalogDirection.y < 0)
            normalizedMagnitude *= -1;

        gamepadEvent.normalizedAnalogMagnitude = normalizedMagnitude;

        return gamepadEvent;
    }

    GamepadEvent SDLInputHandler::MapControllerTriggerMovement(GamepadEvent &gamepadEvent) const
    {
        float magnitude = gamepadEvent.gamepadCode == KeyCode::LeftTrigger
                ? _currentLeftTriggerValue
                : _currentRightTriggerValue;

        float normalizedMagnitude = 0.0f;

        if (magnitude > TRIGGER_DEADZONE)
        {
            if (magnitude > MAXIMUM_AXIS_VALUE)
                magnitude = static_cast<float>(MAXIMUM_AXIS_VALUE);

            normalizedMagnitude = magnitude / (MAXIMUM_AXIS_VALUE - TRIGGER_DEADZONE);
        }
        else
        {
            normalizedMagnitude = 0.0f;
        }

        if (gamepadEvent.gamepadCode == KeyCode::LeftTrigger)
            gamepadEvent.normalizedLeftTriggerMagnitude = normalizedMagnitude;
        else
            gamepadEvent.normalizedRightTriggerMagnitude = normalizedMagnitude;

        return gamepadEvent;
    }

    uint32_t SDLInputHandler::AxisThreshold(KeyCode gamepadCode) const
    {
        return gamepadCode == KeyCode::LeftAnalog
               ? LEFT_ANALOG_AXIS_DEADZONE
               : RIGHT_ANALOG_AXIS_DEADZONE;
    }

    glm::vec2 SDLInputHandler::NormalizeCurrentAnalogDirection(KeyCode gamepadCode, float magnitude) const
    {
        if (gamepadCode == KeyCode::LeftAnalog)
        {
            return
                    {
                            _currentLeftAxisValue.x / magnitude,
                            _currentLeftAxisValue.y / magnitude
                    };
        }

        return
                {
                        _currentRightAxisValue.x / magnitude,
                        _currentRightAxisValue.y / magnitude
                };
    }

    float SDLInputHandler::MagnitudeOfCurrentAnalog(KeyCode gamepadCode) const
    {
        if (gamepadCode == KeyCode::LeftAnalog)
        {
            return sqrt(
                    _currentLeftAxisValue.x * _currentLeftAxisValue.x
                    + _currentLeftAxisValue.y * _currentLeftAxisValue.y);
        }

        return sqrt(
                _currentRightAxisValue.x * _currentRightAxisValue.x
                + _currentRightAxisValue.y * _currentRightAxisValue.y);
    }

    bool SDLInputHandler::GetNextGamepadEvent(GamepadEvent& gamepadEvent)
    {
        if (!_gamepadEventQueue.empty())
        {
            gamepadEvent = _gamepadEventQueue.top();
            _gamepadEventQueue.pop();

            return true;
        }

        return false;
    }

    bool SDLInputHandler::GetNextKeyEvent(KeyEvent& keyEvent)
    {
        if (!_keyboardEventQueue.empty())
        {
            keyEvent = _keyboardEventQueue.top();
            _keyboardEventQueue.pop();

            return true;
        }

        return false;
    }

    Input::ContextType SDLInputHandler::GetFirstActiveInputSource()
    {
        bool isKeyboardQueueNonEmpty = !_keyboardEventQueue.empty();
        bool isGamepadQueueNonEmpty = !_gamepadEventQueue.empty();

        if (isKeyboardQueueNonEmpty && isGamepadQueueNonEmpty)
        {
            auto key = _keyboardEventQueue.top();
            auto gamepad = _gamepadEventQueue.top();

            if (key.timestamp >= gamepad.timestamp)
            {
                EmptyGamepadQueue();
                return Input::ContextType::Keyboard;
            }

            EmptyKeyboardQueue();
            return Input::ContextType::Gamepad;
        }

        if (isKeyboardQueueNonEmpty) return Input::ContextType::Keyboard;
        return Input::ContextType::Gamepad;
    }

    void SDLInputHandler::EmptyGamepadQueue()
    {
        std::priority_queue<GamepadEvent, std::vector<GamepadEvent>, std::greater<GamepadEvent>> empty;
        std::swap(_gamepadEventQueue, empty);
    }

    void SDLInputHandler::EmptyKeyboardQueue()
    {
        std::priority_queue<KeyEvent, std::vector<KeyEvent>, std::greater<KeyEvent>> empty;
        std::swap(_keyboardEventQueue, empty);
    }
};