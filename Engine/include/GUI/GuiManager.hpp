#pragma once

#include <RmlUi/Core.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Debugger/Debugger.h>

#include "glm/glm.hpp"

#include "GUI/RenderInterface.hpp"
#include "GUI/SystemInterface.hpp"
#include "Windowing/Window.hpp"

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