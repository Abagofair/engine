#include <Engine/Input/InputHandler.hpp>

namespace Engine::Input
{
    InputHandler::InputHandler()
    {
        _callbackByGamepadCode = std::unordered_map<GamepadCode, std::function<void(GamepadEvent)>>();
        _gamepadEventQueue = std::priority_queue<GamepadEvent, std::vector<GamepadEvent>, std::greater<GamepadEvent>>();

        _callbackByKeyCode = std::unordered_map<KeyCode, std::function<void(KeyEvent)>>();
        _keyboardEventQueue = std::priority_queue<KeyEvent, std::vector<KeyEvent>, std::greater<KeyEvent>>();
    }

    void InputHandler::FeedEventQueue()
    {
        SDL_Event event;

        //todo: should log if this fails
        _gamepadEventQueue.empty();
        _keyboardEventQueue.empty();

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
                case SDL_KEYUP:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                    }
                    break;
                default:
                    break;
            }
        }
    }

    void InputHandler::ControllerButtonDown(SDL_Event event)
    {
        GamepadEvent gamepadEvent{};

        gamepadEvent.inputEventType = InputEventType::GamePadButtonDown;
        if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
        {
            gamepadEvent.gamepadCode = GamepadCode::GamepadButtonA;
        }
        else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
        {
            gamepadEvent.gamepadCode = GamepadCode::GamepadButtonB;
        }

        _gamepadEventQueue.push(gamepadEvent);
    }

    void InputHandler::ControllerAxisMotion(SDL_Event event)
    {
        GamepadEvent gamepadEvent{};

        auto axis = static_cast<SDL_GameControllerAxis>(event.caxis.axis);
        if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX)
        {
            gamepadEvent.gamepadCode = GamepadCode::GamepadLeftAxis;
            _currentLeftAxisValue.x = event.caxis.value;
            MapControllerAnalogMovement(gamepadEvent);
        }
        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY)
        {
            gamepadEvent.gamepadCode = GamepadCode::GamepadLeftAxis;
            _currentLeftAxisValue.y = event.caxis.value;
            MapControllerAnalogMovement(gamepadEvent);
        }
        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX)
        {
            gamepadEvent.gamepadCode = GamepadCode::GamepadRightAxis;
            _currentRightAxisValue.x = event.caxis.value;
            MapControllerAnalogMovement(gamepadEvent);
        }
        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY)
        {
            gamepadEvent.gamepadCode = GamepadCode::GamepadRightAxis;
            _currentRightAxisValue.y = event.caxis.value;
            MapControllerAnalogMovement(gamepadEvent);
        }
        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT)
        {
            gamepadEvent.gamepadCode = GamepadCode::GamepadLeftTrigger;
            _currentLeftTriggerValue = event.caxis.value;
            MapControllerTriggerMovement(gamepadEvent);
        }
        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
        {
            gamepadEvent.gamepadCode = GamepadCode::GamepadRightTrigger;
            _currentRightTriggerValue = event.caxis.value;
            MapControllerTriggerMovement(gamepadEvent);
        }

        _gamepadEventQueue.push(gamepadEvent);
    }

    GamepadEvent InputHandler::MapControllerAnalogMovement(GamepadEvent &gamepadEvent) const
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

    GamepadEvent InputHandler::MapControllerTriggerMovement(GamepadEvent &gamepadEvent) const
    {
        float magnitude = gamepadEvent.gamepadCode == GamepadLeftTrigger
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

        if (gamepadEvent.gamepadCode == GamepadLeftTrigger)
            gamepadEvent.normalizedLeftTriggerMagnitude = normalizedMagnitude;
        else
            gamepadEvent.normalizedRightTriggerMagnitude = normalizedMagnitude;

        return gamepadEvent;
    }

    uint32_t InputHandler::AxisThreshold(GamepadCode gamepadCode) const
    {
        return gamepadCode == GamepadCode::GamepadLeftAxis
               ? LEFT_ANALOG_AXIS_DEADZONE
               : RIGHT_ANALOG_AXIS_DEADZONE;
    }

    glm::vec2 InputHandler::NormalizeCurrentAnalogDirection(GamepadCode gamepadCode, float magnitude) const
    {
        if (gamepadCode == GamepadCode::GamepadLeftAxis)
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

    float InputHandler::MagnitudeOfCurrentAnalog(GamepadCode gamepadCode) const
    {
        if (gamepadCode == GamepadCode::GamepadLeftAxis)
        {
            return sqrt(
                    _currentLeftAxisValue.x * _currentLeftAxisValue.x
                    + _currentLeftAxisValue.y * _currentLeftAxisValue.y);
        }

        return sqrt(
                _currentRightAxisValue.x * _currentRightAxisValue.x
                + _currentRightAxisValue.y * _currentRightAxisValue.y);
    }

    void InputHandler::DispatchEvents()
    {
        DispatchGamepadEvents();
        DispatchKeyboardEvents();
    }

    void InputHandler::DispatchGamepadEvents()
    {
        while (!_gamepadEventQueue.empty())
        {
            GamepadEvent event = _gamepadEventQueue.top();

            auto callback = _callbackByGamepadCode.find(event.gamepadCode);
            if (callback != _callbackByGamepadCode.end())
            {
                callback->second(event);
            }

            _gamepadEventQueue.pop();
        }
    }

    void InputHandler::DispatchKeyboardEvents()
    {
        while (!_keyboardEventQueue.empty())
        {
            KeyEvent event = _keyboardEventQueue.top();
            auto callback = _callbackByKeyCode.find(event.keyCode);
            if (callback != _callbackByKeyCode.end())
            {
                callback->second(event);
            }

            _keyboardEventQueue.pop();
        }
    }

    void InputHandler::OnGamepadEvent(GamepadCode gamePadCode, std::function<void(GamepadEvent)> callback)
    {
        _callbackByGamepadCode[gamePadCode] = callback;
    }
};