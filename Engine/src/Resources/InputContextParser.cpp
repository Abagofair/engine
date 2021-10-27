#include "InputContextParser.hpp"

namespace Engine::Resources
{
    Input::InputContext* InputContextParser::CreateContext(std::string fileName,
                                                           const std::vector<Input::Action<Input::KeyEvent>>& actions)
    {
        Input::InputContext* inputContext = new Input::InputContext();

        boost::property_tree::ptree tree;
        boost::property_tree::read_ini(fileName, tree);
        for (auto section : tree)
        {
            for (auto codeAction : section.second)
            {
                std::string keyCode = codeAction.first.data();
                std::string actionValue = codeAction.second.data();

                Input::KeyCode gotKeyCode;
                if (!TryGetKeyCode(keyCode, gotKeyCode))
                {
                    std::cout << "couldnt parse keycode" << std::endl;
                }

                std::function<void(Input::KeyEvent)> fp;
                if (!TryGetAction(actions, actionValue, fp))
                {
                    std::cout << "couldnt parse action" << std::endl;
                }

                inputContext->OnKeyPressed(gotKeyCode, fp);
            }
        }

        return inputContext;
    }

    bool InputContextParser::TryGetKeyCode(std::string value,
                                           Input::KeyCode& keyCode)
    {
        for (int i = 0; i < Input::KeyCodeStrings.size(); ++i)
        {
            auto& str = Input::KeyCodeStrings[i];
            if (value == str)
            {
                keyCode = static_cast<Input::KeyCode>(i);
                return true;
            }
        }

        return false;
    }

    bool InputContextParser::TryGetAction(const std::vector<Input::Action<Input::KeyEvent>>& actions,
                                          std::string value,
                                          std::function<void(Input::KeyEvent)>& fp)
    {
        fp = nullptr;

        for (int i = 0; i < actions.size(); ++i)
        {
            auto& action = actions[i];
            if (value == action.functionName)
            {
                fp = action.functionPointer;
                return true;
            }
        }

        return false;
    }
};