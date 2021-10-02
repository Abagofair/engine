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
        GamepadEvent gamepadEvent {};

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
        GamepadEvent gamepadEvent {};

        auto axis = static_cast<SDL_GameControllerAxis>(event.caxis.axis);
        if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX)
        {
            gamepadEvent.gamepadCode = GamepadCode::GamepadLeftAxis;
            _currentLeftAxisValues.x = event.caxis.value;
        }
        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY)
        {
            gamepadEvent.gamepadCode = GamepadCode::GamepadLeftAxis;
            _currentLeftAxisValues.y = event.caxis.value;
        }
        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX)
        {
            gamepadEvent.gamepadCode = GamepadCode::GamepadRightAxis;
            _currentRightAxisValues.x = event.caxis.value;
        }
        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY)
        {
            gamepadEvent.gamepadCode = GamepadCode::GamepadRightAxis;
            _currentRightAxisValues.y = event.caxis.value;
        }

        MapControllerAxisMovement(gamepadEvent);
        _gamepadEventQueue.push(gamepadEvent);
    }

    GamepadEvent InputHandler::MapControllerAxisMovement(GamepadEvent& gamepadEvent) const
    {
        float magnitude;
        float normalizedMagnitude;

        //https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput
        //determine how far the controller is pushed
        magnitude = MagnitudeOfCurrentAxis(gamepadEvent.gamepadCode);

        //determine the direction the controller is pushed
        gamepadEvent.normalizedDirection = NormalizeCurrentAxisDirection(gamepadEvent.gamepadCode, magnitude);

        uint32_t axisThreshold = AxisThreshold(gamepadEvent.gamepadCode);

        if (magnitude > axisThreshold)
        {
            //clip the magnitude at its expected maximum value
            if (magnitude > MAXIMUM_AXIS_VALUE) magnitude = MAXIMUM_AXIS_VALUE;

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

        if (gamepadEvent.normalizedDirection.y < 0)
            normalizedMagnitude *= -1;

        gamepadEvent.normalizedMagnitude = normalizedMagnitude;

        return gamepadEvent;
    }

    uint32_t InputHandler::AxisThreshold(GamepadCode gamepadCode) const
    {
        return gamepadCode == GamepadCode::GamepadLeftAxis
            ? LEFT_AXIS_THRESHOLD
            : RIGHT_AXIS_THRESHOLD;
    }

    glm::vec2 InputHandler::NormalizeCurrentAxisDirection(GamepadCode gamepadCode, float magnitude) const
    {
        if (gamepadCode == GamepadCode::GamepadLeftAxis)
        {
            return
            {
                _currentLeftAxisValues.x / magnitude,
                _currentLeftAxisValues.y / magnitude
            };
        }

        return
        {
            _currentRightAxisValues.x / magnitude,
            _currentRightAxisValues.y / magnitude
        };
    }

    float InputHandler::MagnitudeOfCurrentAxis(GamepadCode gamepadCode) const
    {
        if (gamepadCode == GamepadCode::GamepadLeftAxis)
        {
            return sqrt(
                    _currentLeftAxisValues.x * _currentLeftAxisValues.x
                    + _currentLeftAxisValues.y * _currentLeftAxisValues.y);
        }

        return sqrt(
                _currentRightAxisValues.x * _currentRightAxisValues.x
                    + _currentRightAxisValues.y * _currentRightAxisValues.y);
    }

    void InputHandler::DispatchEvents()
    {
        DispatchGamepadEvents();
        DispatchKeyboardEvents();
    }

    void InputHandler::DispatchGamepadEvents()
    {
        while(!_gamepadEventQueue.empty())
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
        while(!_keyboardEventQueue.empty())
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