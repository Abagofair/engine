#pragma once

#include <Input/InputStructures.hpp>
#include <functional>
#include <unordered_map>
#include <queue>

#include <SDL.h>

namespace Input
{
    class InputHandler
    {
    public:
        InputHandler();

        void FeedEventQueue();
        void DispatchEvents();

        void OnKeyPressed(InputCode keyCode, std::function<void(OnKeyEventArgs)> callback);
        void OnKeyReleased(InputCode keyCode, std::function<void(OnKeyEventArgs)> callback);

        /*void OnMouseButtonDown(KeyCode, Function);
        void OnMouseButtonUp(KeyCode, Function);
        void OnMouseMoved(KeyCode, Function);*/

        void OnGameAxisMoved(InputCode gamePadCode, std::function<void(EventArgs)> callback);
        /*void OnGamePadButtonDown(KeyCode, Function);
        void OnGamePadButtonUp(KeyCode, Function);*/

    private:
        std::unordered_map<InputCode, std::function<void(EventArgs)>> _callbackByInputCode;
        std::priority_queue<Input, std::vector<Input>, std::greater<Input>> _eventQueue;

        /*void HandleKeyPressed(KeyCode, Function);
        void HandleKeyReleased(KeyCode, Function);*/

        /*void HandleMouseButtonDown(KeyCode, Function);
        void HandleMouseButtonUp(KeyCode, Function);
        void HandleMouseMoved(KeyCode, Function);*/

        void HandleGameAxisMoved();
        /*void HandleGamePadButtonDown(KeyCode, Function);
        void HandleGamePadButtonUp(KeyCode, Function);*/
    };
};