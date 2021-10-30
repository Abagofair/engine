#pragma once

#include <cstdint>
#include <functional>
#include <string>

#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

#include "External/include/glm/glm.hpp"

namespace Engine::Input
{

#define SHITE_INPUT_KEYCODES_ENUM(ENUM_NAME, CODES...) enum class ENUM_NAME { CODES };
#define STRINGIFY(r, data, elem) BOOST_PP_STRINGIZE(elem),
#define SHITE_INPUT_KEYCODES_ARRAY(ARRAY_NAME, CODES...) static const std::vector<std::string> ARRAY_NAME = { BOOST_PP_SEQ_FOR_EACH(STRINGIFY, _, BOOST_PP_VARIADIC_TO_SEQ(CODES)) };
#define SHITE_INPUT_CODES(ENUM_NAME, ARRAY_NAME, CODES...) \
SHITE_INPUT_KEYCODES_ENUM(ENUM_NAME, CODES)             \
SHITE_INPUT_KEYCODES_ARRAY(ARRAY_NAME, CODES)

    SHITE_INPUT_CODES(KeyCode, KeyCodeStrings,
                      A,
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
                      ESC,
                      LeftAnalog,
                      RightAnalog,
                      GamepadA,
                      GamepadB,
                      GamePadStart,
                      LeftTrigger,
                      RightTrigger)

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

    /*enum KeyCode
    {
        A,
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
        ESC
    };*/

    enum GamepadCode
    {
        GamepadLeftAxis = 100,
        GamepadRightAxis,
        GamepadButtonA,
        GamepadButtonB,
        GamepadLeftTrigger,
        GamepadRightTrigger
    };

    struct InputEvent
    {
        uint32_t priority;
        InputEventType inputEventType;
        uint32_t timestamp;

        friend bool operator> (const InputEvent& l, const InputEvent& r)
        {
            return l.priority > r.priority;
        }
    };

    struct GamepadEvent : public InputEvent
    {
        KeyCode gamepadCode;
        glm::vec2 normalizedAnalogDirection;
        float normalizedAnalogMagnitude;
        float normalizedLeftTriggerMagnitude;
        float normalizedRightTriggerMagnitude;
    };

    struct KeyEvent : public InputEvent
    {
        KeyCode keyCode;
    };

    template<typename T>
    struct Action
    {
        std::string functionName;
        std::function<void(T)> functionPointer;
    };

    enum class ContextType
    {
        Gamepad,
        Keyboard
    };

#define SHITE_INPUT_LAMBDA(EVENT, FUNC) [this](Engine::Input::EVENT e) { FUNC(e); }
#define SHITE_INPUT_GAMEPAD_ACTION(NAME, EVENT, FUNC) Engine::Input::Action<Engine::Input::EVENT> { NAME, SHITE_INPUT_LAMBDA(EVENT, FUNC)},
};