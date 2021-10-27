#include "InputContextParser.hpp"

namespace Engine::Resources
{
    Input::InputContext* InputContextParser::CreateContext(std::string fileName,
                                                           const std::vector<Input::Action<Input::KeyEvent>>& actions)
    {
        tinyxml2::XMLDocument doc;
        doc.LoadFile(fileName.c_str());

        if (doc.Error())
        {
            std::cout << "Error parsing document: " << fileName << std::endl;
        }

        Input::InputContext* inputContext = new Input::InputContext();

        tinyxml2::XMLElement* root = doc.RootElement();
        auto playingContext = root->NextSiblingElement("Context");
        auto keyboard = playingContext->FirstChildElement("Keyboard");
        auto entry = keyboard->NextSiblingElement("Entry");
        auto code = entry->FirstChildElement("Code");
        auto action = entry->FirstChildElement("Action");

        std::string keyCode = code->Value();
        std::string actionValue = action->Value();

        return inputContext;
    }

    bool InputContextParser::TryGetKeyCode(std::string value, Input::KeyCode& keyCode)
    {
        for (int i = 0; i < Input::KeyCodeStrings.size(); ++i)
        {
            auto& str = Input::KeyCodeStrings[i];
            if (value == str)
                return true;
        }

        return false;
    }

    bool InputContextParser::TryGetAction(const std::vector<Input::Action<Input::KeyEvent>>& actions, std::string value, std::function<void(Input::KeyEvent)>& fp)
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