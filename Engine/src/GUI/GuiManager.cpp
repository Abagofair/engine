#include "GuiManager.hpp"

namespace Engine::GUI
{
    GuiManager::GuiManager(Engine::Windowing::Window* window,
                           Rendering::ShaderManager& shaderManager,
                           glm::mat4 viewMatrix)
        : _renderInterface(window, shaderManager, viewMatrix)
    {
        Rml::SetRenderInterface(&_renderInterface);
        Rml::SetSystemInterface(&_systemInterface);
        Rml::Initialise();

        _context = Rml::CreateContext("main",
                                      Rml::Vector2i(window->WindowDimensions().x,
                                                    window->WindowDimensions().y));

        if (!_context)
        {
            std::cout << "Rml::Context failed" << std::endl;
            Rml::Shutdown();
        }

        Rml::LoadFontFace("LatoLatin-Regular.ttf");
    }

    Rml::ElementDocument* GuiManager::LoadDocument(std::string documentName)
    {
        Rml::ElementDocument* document = _context->LoadDocument(documentName);
        if (!document)
        {
            std::cout << "Rml::ElementDocument failed" << std::endl;
            Rml::Shutdown();
        }

        document->Show();

        return document;
    }

    void GuiManager::LoadInGameMenuDocument()
    {
        _currentDocument = LoadDocument("hello_world.rml");
    }

    void GuiManager::Update()
    {
        //_currentDocument->GetElementById("a")->SetPseudoClass("hover", false);
        _context->Update();
    }

    void GuiManager::Draw()
    {
        _context->Render();
    }
};