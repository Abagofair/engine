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
        bool asd = false;
        SDL_Event event;

        std::vector<GamepadEvent> gamepadEvents;

        _gamepadEventQueue.empty();
        _keyboardEventQueue.empty();
        
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_CONTROLLERAXISMOTION:
                    {
                        asd = true;
                        GamepadEvent gamepadEvent;
                        gamepadEvent.inputEventType = InputEventType::GamePadAxisMoved;
                        
                        auto axis = static_cast<SDL_GameControllerAxis>(event.caxis.axis);
                        if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX)
                        {
                            gamepadEvent.gamepadCode = GamepadCode::GamepadLeftAxis;
                            _leftAxisValues.x = event.caxis.value;
                        }
                        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY)
                        {
                            gamepadEvent.gamepadCode = GamepadCode::GamepadLeftAxis;
                            _leftAxisValues.y = event.caxis.value;
                        }
                        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX)
                        {
                            gamepadEvent.gamepadCode = GamepadCode::GamepadRightAxis;
                            _rightAxisValues.x = event.caxis.value;
                        }
                        else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY)
                        {
                            gamepadEvent.gamepadCode = GamepadCode::GamepadRightAxis;
                            _rightAxisValues.y = event.caxis.value;
                        }

                        gamepadEvents.push_back(gamepadEvent);
                        break;
                    }
                case SDL_CONTROLLERBUTTONDOWN:
                    {
                        GamepadEvent gamepadEvent;

                        gamepadEvent.inputEventType = InputEventType::GamePadButtonDown;
                        if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
                        {
                            gamepadEvent.gamepadCode = GamepadCode::GamepadButtonA;
                        }
                        else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
                        {
                            gamepadEvent.gamepadCode = GamepadCode::GamepadButtonB;
                        }

                        gamepadEvents.push_back(gamepadEvent);
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

        for (GamepadEvent ge : gamepadEvents)
        {
            float magnitude = 0.0f;
            float normalizedLX = 0.0f;
            float normalizedLY = 0.0f;
            float normalizedMagnitude = 0.0f;

            //TODO: mmm duplication
            if (ge.gamepadCode == GamepadCode::GamepadLeftAxis)
            {
                //https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput
                //determine how far the controller is pushed
                magnitude = sqrt(_leftAxisValues.x * _leftAxisValues.x
                    + _leftAxisValues.y * _leftAxisValues.y);

                //determine the direction the controller is pushed
                normalizedLX = _leftAxisValues.x / magnitude;
                normalizedLY = _leftAxisValues.y / magnitude;

                normalizedMagnitude = 0;

                if (magnitude > 7849)
                {
                    //clip the magnitude at its expected maximum value
                    if (magnitude > 32767) magnitude = 32767;

                    //adjust magnitude relative to the end of the dead zone
                    magnitude -= 7849;

                    //optionally normalize the magnitude with respect to its expected range
                    //giving a magnitude value of 0.0 to 1.0
                    normalizedMagnitude = magnitude / (32767 - 7849);
                }
                else //if the controller is in the deadzone zero out the magnitude
                {
                    magnitude = 0.0;
                    normalizedMagnitude = 0.0;
                }

                if (normalizedLY < 0)
                    normalizedMagnitude *= -1;
            }
            else if (ge.gamepadCode == GamepadCode::GamepadRightAxis)
            {
                //https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput
                //determine how far the controller is pushed
                magnitude = sqrt(_rightAxisValues.x * _rightAxisValues.x
                    + _rightAxisValues.y * _rightAxisValues.y);

                //determine the direction the controller is pushed
                normalizedLX = _rightAxisValues.x / magnitude;
                normalizedLY = _rightAxisValues.y / magnitude;

                normalizedMagnitude = 0;

                if (magnitude > 8689)
                {
                    //clip the magnitude at its expected maximum value
                    if (magnitude > 32767) magnitude = 32767;

                    //adjust magnitude relative to the end of the dead zone
                    magnitude -= 8689;

                    //optionally normalize the magnitude with respect to its expected range
                    //giving a magnitude value of 0.0 to 1.0
                    normalizedMagnitude = magnitude / (32767 - 8689);
                }
                else //if the controller is in the deadzone zero out the magnitude
                {
                    magnitude = 0.0;
                    normalizedMagnitude = 0.0;
                }

                if (normalizedLY < 0)
                    normalizedMagnitude *= -1;
            }

            ge.normalizedMagnitude = normalizedMagnitude;
            ge.normalizedDirection = glm::vec2(normalizedLX, normalizedLY);

            _gamepadEventQueue.push(ge);
        }
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