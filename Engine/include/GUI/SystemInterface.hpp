#pragma once

#include <iostream>

#include <SDL.h>
#include <RmlUi/Core/SystemInterface.h>
#include <RmlUi/Core/Input.h>

namespace Engine::GUI
{
    class SystemInterface : public Rml::SystemInterface
    {
    public:
        Rml::Input::KeyIdentifier TranslateKey(SDL_Keycode sdlkey);
        //int TranslateMouseButton(Uint8 button);
        //int GetKeyModifiers();

        double GetElapsedTime() override;
        bool LogMessage(Rml::Log::Type type, const Rml::String& message) override;
    };
};