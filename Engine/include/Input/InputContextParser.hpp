#pragma once

#include <functional>
#include <string>
#include <vector>
#include <iostream>

#include <boost/property_tree/ini_parser.hpp>

#include "InputContext.hpp"
#include "InputStructures.hpp"

namespace Engine::Input
{
    class InputContextParser
    {
    public:

        Input::InputContext *CreateGamepadContext(const std::string &fileName,
                                                  const std::vector<Input::Action<Input::GamepadEvent>> &actions);

        Input::InputContext *CreateKeyboardContext(const std::string &fileName,
                                                   const std::vector<Input::Action<Input::KeyEvent>> &actions);

    private:
        template<typename T>
        void CreateContext(const std::string &fileName,
                           const std::string &sectionName,
                           const std::vector<Input::Action<T>> &actions,
                           const Input::InputContext& inputContext,
                           std::function<void(Input::KeyCode, std::function<void(T)>)> registerEvent);

        bool TryGetKeyCode(
                const std::string &value,
                Input::KeyCode &keyCode);

        template<typename T>
        bool TryGetAction(
                const std::vector<Input::Action<T>> &actions,
                const std::string &value,
                std::function<void(T)> &fp);
    };
};