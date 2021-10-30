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

#include "Engine/include/Input/InputStructures.hpp"

namespace Engine::Input
{
    class SDLInputHandler
    {
    public:

        void FeedEventQueue();

        bool GetNextGamepadEvent(GamepadEvent& gamepadEvent);
        bool GetNextKeyEvent(KeyEvent& keyEvent);

        bool GetFirstActiveInputSource(Input::ContextType& contextType);
    private:
        std::priority_queue<GamepadEvent, std::vector<GamepadEvent>, std::greater<GamepadEvent>> _gamepadEventQueue;
        std::priority_queue<KeyEvent, std::vector<KeyEvent>, std::greater<KeyEvent>> _keyboardEventQueue;

        /*
         * the below values and functions should be in something else?
         */
        glm::vec2 _currentLeftAxisValue;
        glm::vec2 _currentRightAxisValue;
        float _currentLeftTriggerValue;
        float _currentRightTriggerValue;

        GamepadEvent MapControllerAnalogMovement(GamepadEvent& gamepadEvent) const;
        GamepadEvent MapControllerTriggerMovement(GamepadEvent& gamepadEvent) const;
        float MagnitudeOfCurrentAnalog(KeyCode gamepadCode) const;
        glm::vec2 NormalizeCurrentAnalogDirection(KeyCode gamepadCode, float magnitude) const;
        uint32_t AxisThreshold(KeyCode gamepadCode) const;

        void EmptyKeyboardQueue();
        void EmptyGamepadQueue();

        //todo: Could be handled in SDL input wrapper
        void ControllerAxisMotion(SDL_Event event);
        void ControllerButtonDown(SDL_Event event);

        static inline uint32_t const TRIGGER_DEADZONE = 30;
        static inline uint32_t const LEFT_ANALOG_AXIS_DEADZONE = 7849;
        static inline uint32_t const RIGHT_ANALOG_AXIS_DEADZONE = 8689;
        static inline uint32_t const MAXIMUM_AXIS_VALUE = 32767;
    };
};