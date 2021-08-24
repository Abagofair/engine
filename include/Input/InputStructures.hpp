#pragma once

#include <cstdint>

namespace Input
{
    enum InputEvent
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

    struct EventArgs
    {
        float value;
    };

    struct OnKeyEventArgs : public EventArgs
    {

    };

    struct OnGamePadAxisMovedEventArgs : public EventArgs
    {

    };

    struct Input
    {
        uint32_t priority;
        InputCode inputCode;
        InputEvent inputEvent;

        float normalizedXDelta;
        float normalizedYDelta;

        bool operator >(Input a)
        {
            return priority > a.priority;
        }
    };

    enum InputCode
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
        Z,
        GamepadLeftAxis,
        GamepadRightAxis
    };
};