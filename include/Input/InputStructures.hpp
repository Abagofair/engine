#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Input
{
    enum InputEventType
    {
        KeyPressed = 0,
        KeyReleased,
        
        MouseButtonDown,
        MouseButtonUp,
        MouseMoved,

        GamePadAxisMoved,
        GamePadButtonDown,
        GamePadButtonUp
    };

    enum KeyCode
    {
        A = 0,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        X,
        Y,
        Z
    };

    enum GamepadCode
    {
        GamepadLeftAxis = 100,
        GamepadRightAxis,
        GamepadButton1
    };

    struct InputEvent
    {
        uint32_t priority;
        InputEventType inputEventType;

        friend bool operator> (const InputEvent& l, const InputEvent& r)
        {
            return l.priority > r.priority;
        }
    };

    struct GamepadEvent : public InputEvent
    {
        GamepadCode gamepadCode;
        glm::vec2 normalizedDirection;
        float normalizedMagnitude;
    };

    struct KeyEvent : public InputEvent
    {  
        KeyCode keyCode;
    };
};