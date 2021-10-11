#pragma once

#include <iostream>
#include <cstdint>

#include <RmlUi/Core/RenderInterface.h>
#include <RmlUi/Core.h>

#include <SDL.h>

#include "External/include/glm/glm.hpp"

#include "GlHelper.hpp"
#include "Window.hpp"
#include "glPortableHeaders.hpp"
#include "ShaderManager.hpp"

namespace Engine::GUI
{
    class RenderInterface : public Rml::RenderInterface
    {
    public:
        RenderInterface(Windowing::Window* window,
                        Rendering::ShaderManager& shaderManager,
                        glm::mat4 viewMatrix);

        /// Called by RmlUi when it wants to render geometry that it does not wish to optimise.
        void RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture, const Rml::Vector2f& translation) override;

        /// Called by RmlUi when it wants to enable or disable scissoring to clip content.
        void EnableScissorRegion(bool enable) override;
        /// Called by RmlUi when it wants to change the scissor region.
        void SetScissorRegion(int x, int y, int width, int height) override;

        /// Called by RmlUi when a texture is required by the library.
        bool LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions, const Rml::String& source) override;
        /// Called by RmlUi when a texture is required to be built from an internally-generated sequence of pixels.
        bool GenerateTexture(Rml::TextureHandle& texture_handle, const Rml::byte* source, const Rml::Vector2i& source_dimensions) override;
        /// Called by RmlUi when a loaded texture is no longer required.
        void ReleaseTexture(Rml::TextureHandle texture_handle) override;

    private:
        Windowing::Window* _window;
        Rendering::ShaderManager& _shaderManager;

        glm::mat4 _viewMatrix;

        uint32_t _bufferElements;
        uint32_t _vbo;
        uint32_t _vao;
    };
};