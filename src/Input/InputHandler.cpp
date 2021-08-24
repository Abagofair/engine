#include <Input/InputHandler.hpp>

using namespace Input;

InputHandler::InputHandler()
{
    _callbackByInputCode = std::unordered_map<InputCode, std::function<void(EventArgs)>>();
    _eventQueue = std::priority_queue<Input, std::vector<Input>, std::greater<Input>>();
}

void InputHandler::FeedEventQueue()
{
    Input input;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_CONTROLLERAXISMOTION:
                {
                    input.priority = 1;
                    input.inputCode = InputCode::GamepadLeftAxis; //TODO: IS WRONG
                    input.inputEvent = InputEvent::GamePadAxisMoved;
                    input.normalizedXDelta = event.caxis.value;
                    _eventQueue.push(input);
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
    while(!_eventQueue.empty()) {
        auto input = _eventQueue.top();
        auto callback = _callbackByInputCode.find(input.inputCode);
        if (callback != _callbackByInputCode.end())
        {
            EventArgs eventArgs;
            eventArgs.value = input.normalizedXDelta;
            callback->second(eventArgs);
        }
    }
}

void InputHandler::OnGameAxisMoved(InputCode gamePadCode, std::function<void(EventArgs)> callback)
{
    _callbackByInputCode[gamePadCode] = callback;
}