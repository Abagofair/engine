#pragma once

#include <cstdint>

#include <vector>
#include <array>
#include <iostream>

#include "External/include/glm/glm.hpp"

#include "glPortableHeaders.hpp"
#include "RenderingComponents.hpp"
#include "RenderingStructures.hpp"
#include "GlHelper.hpp"

namespace Engine::Rendering
{
    std::array<Rendering::Structures::Vertex, 4> CreateVertices(uint32_t width, uint32_t height, std::array<Rendering::Structures::RGBA, 4> colors);
    Rendering::Components::RenderableComponent SetupDynamic(uint32_t textureHandle, uint32_t shaderHandle, uint32_t width, uint32_t height);
    Rendering::Components::DebugRenderableComponent SetupDebug(uint32_t shaderHandle, uint32_t width, uint32_t height);
    Rendering::Components::StaticRenderableComponent SetupStatic(uint32_t textureHandle, uint32_t shaderHandle, std::vector<glm::mat4> transforms, uint32_t width, uint32_t height);
};