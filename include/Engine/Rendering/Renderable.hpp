#pragma once

#include <cstdint>

#include <vector>

#include <External/glm/glm.hpp>

#include <Engine/Global/glPortableHeaders.hpp>
#include <Engine/Rendering/RenderingComponents.hpp>

namespace Engine::Rendering::Renderable
{
    struct Renderable
    {
        uint32_t vbo;
        uint32_t vao;
        uint32_t ebo;
    };

    struct Static
    {
        uint32_t vbo;
        uint32_t vao;
        uint32_t ebo;
        uint32_t shaderId;
        uint32_t instances;
    };

    struct Dynamic
    {
        uint32_t vbo;
        uint32_t vao;
        uint32_t ebo;
        uint32_t shaderId;
    };

    void SetupVboEbo(uint32_t &vbo, uint32_t &vao, uint32_t &ebo, float width, float height);
    Rendering::Components::RenderableComponent SetupDynamic(uint32_t shaderId, uint32_t width, uint32_t height);
    Rendering::Components::DebugRenderableComponent SetupDebug(uint32_t shaderId, uint32_t width, uint32_t height);
    Rendering::Components::StaticRenderableComponent SetupStatic(uint32_t shaderId, std::vector<glm::mat4> transforms, uint32_t width, uint32_t height);
};