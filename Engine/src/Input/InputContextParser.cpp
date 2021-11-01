#include "Input/InputContextParser.hpp"

namespace Engine::Input
{
    Input::InputContext *InputContextParser::CreateGamepadContext(const std::string &fileName,
                                                                  const std::vector<Input::Action<Input::GamepadEvent>> &actions,
                                                                  Input::SDLInputHandler &inputHandler)
    {
        Input::InputContext *inputContext = new Input::InputContext(inputHandler);
        auto fp = std::bind(&Input::InputContext::OnGamepadEvent, inputContext, std::placeholders::_1,
                            std::placeholders::_2);

        CreateContext<Input::GamepadEvent>(fileName, "Gamepad", actions, *inputContext, fp);
        return inputContext;
    }

    Input::InputContext *InputContextParser::CreateKeyboardContext(const std::string &fileName,
                                                                   const std::vector<Input::Action<Input::KeyEvent>> &actions,
                                                                   Input::SDLInputHandler &inputHandler)
    {
        Input::InputContext *inputContext = new Input::InputContext(inputHandler);
        auto fp = std::bind(&Input::InputContext::OnKeyPressed, inputContext, std::placeholders::_1,
                            std::placeholders::_2);
        CreateContext<Input::KeyEvent>(fileName, "Keyboard", actions, *inputContext, fp);
        return inputContext;
    }

    template<typename T>
    void InputContextParser::CreateContext(const std::string &fileName,
                                           const std::string &sectionName,
                                           const std::vector<Input::Action<T>> &actions,
                                           const Input::InputContext &inputContext,
                                           std::function<void(Input::KeyCode, std::function<void(T)>)> registerEvent)
    {
        boost::property_tree::ptree tree;
        boost::property_tree::read_ini(fileName, tree);
        for (auto section: tree)
        {
            if (section.first.data() != sectionName)
                continue;

            for (auto codeAction: section.second)
            {
                std::string keyCode = codeAction.first.data();
                std::string actionValue = codeAction.second.data();

                Input::KeyCode gotKeyCode;
                if (!TryGetKeyCode(keyCode, gotKeyCode))
                {
                    std::cout << "couldnt parse keycode" << std::endl;
                }

                std::function < void(T) > fp;
                if (!TryGetAction<T>(actions, actionValue, fp))
                {
                    std::cout << "couldnt parse action" << std::endl;
                }

                std::invoke(registerEvent, gotKeyCode, fp);
            }
        }
    }

    bool InputContextParser::TryGetKeyCode(
            const std::string &value,
            Input::KeyCode &keyCode)
    {
        for (int i = 0; i < Input::KeyCodeStrings.size(); ++i)
        {
            auto &str = Input::KeyCodeStrings[i];
            if (value == str)
            {
                keyCode = static_cast<Input::KeyCode>(i);
                return true;
            }
        }

        return false;
    }

    template<typename T>
    bool InputContextParser::TryGetAction(
            const std::vector<Input::Action<T>> &actions,
            const std::string &value,
            std::function<void(T)> &fp)
    {
        fp = nullptr;

        for (int i = 0; i < actions.size(); ++i)
        {
            auto &action = actions[i];
            if (value == action.functionName)
            {
                fp = action.functionPointer;
                return true;
            }
        }

        return false;
    }
};