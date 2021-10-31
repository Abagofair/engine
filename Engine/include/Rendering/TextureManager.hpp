#pragma once

#include <SDL_image.h>

#include <unordered_map>

#include "Resources/ResourceHandler.hpp"
#include "Rendering/RenderingStructures.hpp"
#include "GLHelpers/GlHelper.hpp"

namespace Engine::Rendering
{
    class TextureManager
    {
    public:
        TextureManager(Resources::ResourceHandler& resourceHandler);

        Rendering::Structures::Texture* TextureFromImage(std::string filePath);

    private:
        std::unordered_map<uint32_t, Rendering::Structures::Texture*> _texturesById;
        Resources::ResourceHandler& _resourceHandler;
    };
};