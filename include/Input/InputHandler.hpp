#pragma once

#include <iostream>

#include <Input/InputStructures.hpp>
#include <functional>
#include <unordered_map>
#include <queue>
#include <stdexcept>
#include <cmath>
#include <SDL.h>
#include <vector>

namespace Input
{
    class InputHandler
    {
    public:
        InputHandler();

        //note: could be a separate system that wraps the SDL_Event queue and feeds the internal queues to this handler
        void FeedEventQueue();
        
        void DispatchEvents();

        void DispatchGamepadEvents();
        void DispatchKeyboardEvents();

        //Subscribe functions
        void OnKeyPressed(KeyCode keyCode, std::function<void(KeyEvent)> callback);
        void OnKeyReleased(KeyCode keyCode, std::function<void(KeyEvent)> callback);

        /*void OnMouseButtonDown(KeyCode, Function);
        void OnMouseButtonUp(KeyCode, Function);
        void OnMouseMoved(KeyCode, Function);*/

        void OnGamepadEvent(GamepadCode gamePadCode, std::function<void(GamepadEvent)> callback);
        /*void OnGamePadButtonDown(KeyCode, Function);
        void OnGamePadButtonUp(KeyCode, Function);*/

    private:
        std::unordered_map<GamepadCode, std::function<void(GamepadEvent)>> _callbackByGamepadCode;
        std::unordered_map<KeyCode, std::function<void(KeyEvent)>> _callbackByKeyCode;

        std::priority_queue<GamepadEvent, std::vector<GamepadEvent>, std::greater<GamepadEvent>> _gamepadEventQueue;
        std::priority_queue<KeyEvent, std::vector<KeyEvent>, std::greater<KeyEvent>> _keyboardEventQueue;

        glm::vec2 _leftAxisValues;
        glm::vec2 _rightAxisValues;
    };
};