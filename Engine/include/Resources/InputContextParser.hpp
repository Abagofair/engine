#pragma once

#include <functional>
#include <string>
#include <vector>
#include <iostream>

#include "tinyxml2.h"

#include "InputContext.hpp"
#include "InputStructures.hpp"

namespace Engine::Resources
{
#define LAMBDA(name) ([this](Engine::Input::KeyEvent){ name(); })

    class InputContextParser
    {
    public:

        Input::InputContext* CreateContext(std::string fileName,
                                           const std::vector<Input::Action<Input::KeyEvent>>& actions);
    private:
        bool TryGetKeyCode(std::string value, Input::KeyCode& keyCode);
        bool TryGetAction(const std::vector<Input::Action<Input::KeyEvent>>& actions, std::string value, std::function<void(Input::KeyEvent)>& fp);
    };
};