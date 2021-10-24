#pragma once

#include <RmlUi/Core.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Debugger/Debugger.h>

#include "External/include/glm/glm.hpp"

#include "RenderInterface.hpp"
#include "SystemInterface.hpp"
#include "Window.hpp"

namespace Engine::GUI
{
    class GuiManager
    {
    public:
        GuiManager(Windowing::Window* window,
                   Rendering::ShaderManager& shaderManager,
                   glm::mat4 viewMatrix);

        void LoadInGameMenuDocument();
        void Update();
        void Draw();

    private:
        GUI::RenderInterface _renderInterface;
        GUI::SystemInterface _systemInterface;

        Rml::Context* _context;
        Rml::ElementDocument* _currentDocument;

        Rml::ElementDocument* LoadDocument(std::string documentName);
    };
};