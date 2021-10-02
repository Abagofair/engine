#pragma once

#include <functional>
#include <unordered_map>
#include <queue>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstdint>

#include <SDL.h>

#include <Engine/Input/InputStructures.hpp>

namespace Engine::Input
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

        glm::vec2 _currentLeftAxisValues;
        glm::vec2 _currentRightAxisValues;

        GamepadEvent MapControllerAxisMovement(GamepadEvent& gamepadEvent) const;
        float MagnitudeOfCurrentAxis(GamepadCode gamepadCode) const;
        glm::vec2 NormalizeCurrentAxisDirection(GamepadCode gamepadCode, float magnitude) const;
        uint32_t AxisThreshold(GamepadCode gamepadCode) const;

        void ControllerAxisMotion(SDL_Event event);
        void ControllerButtonDown(SDL_Event event);

        static inline uint32_t const LEFT_AXIS_THRESHOLD = 7849;
        static inline uint32_t const RIGHT_AXIS_THRESHOLD = 8689;
        static inline uint32_t const MAXIMUM_AXIS_VALUE = 32767;
    };
};