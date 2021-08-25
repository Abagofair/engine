#include <Input/InputHandler.hpp>

using namespace Input;

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
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_CONTROLLERAXISMOTION:
                {
                    GamepadEvent gamepadEvent;
                    gamepadEvent.inputEventType = InputEventType::GamePadAxisMoved;
                    
                    auto axis = static_cast<SDL_GameControllerAxis>(event.caxis.axis);
                    if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX ||
                        axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY)
                    {
                        gamepadEvent.gamepadCode = GamepadCode::GamepadLeftAxis;
                    }
                    else if (axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX ||
                        axis == SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY)
                    {
                        gamepadEvent.gamepadCode = GamepadCode::GamepadRightAxis;
                    }

                    gamepadEvent.normalizedAxisValue = 1000.0f / event.caxis.value;

                    _gamepadEventQueue.push(gamepadEvent);

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

void InputHandler::OnGamepadAxisMoved(GamepadCode gamePadCode, std::function<void(GamepadEvent)> callback)
{
    _callbackByGamepadCode[gamePadCode] = callback;
}