#include "GUI/SystemInterface.hpp"

namespace Engine::GUI
{
    Rml::Input::KeyIdentifier SystemInterface::TranslateKey(SDL_Keycode sdlkey)
    {
        switch (sdlkey)
        {
            case SDLK_ESCAPE:
                return Rml::Input::KI_ESCAPE;
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                return Rml::Input::KI_UP;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                return Rml::Input::KI_DOWN;
            case SDL_CONTROLLER_BUTTON_A:
                return Rml::Input::KI_RETURN;
            default:
                return Rml::Input::KI_UNKNOWN;
        }
    }

    double SystemInterface::GetElapsedTime()
    {
        return double(SDL_GetTicks()) / 1000.0;
    }

    bool SystemInterface::LogMessage(Rml::Log::Type type, const Rml::String& message)
    {
        /*Rml::String Type;

        switch(type)
        {
            case Rml::Log::LT_ALWAYS:
                Type = "[Always]";
                break;
            case Rml::Log::LT_ERROR:
                Type = "[Error]";
                break;
            case Rml::Log::LT_ASSERT:
                Type = "[Assert]";
                break;
            case Rml::Log::LT_WARNING:
                Type = "[Warning]";
                break;
            case Rml::Log::LT_INFO:
                Type = "[Info]";
                break;
            case Rml::Log::LT_DEBUG:
                Type = "[Debug]";
                break;
            case Rml::Log::LT_MAX:
                break;
        };

        printf("%s - %s\n", Type.c_str(), message.c_str());

        return true;*/

        std::cout << message << std::endl;

        return true;
    }
};