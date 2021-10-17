#pragma once

#include <array>
#include <cstdint>

#include "External/include/glm/glm.hpp"

namespace Engine::Rendering::Structures
{
    struct Texture
    {
        std::string filePath;
        uint32_t resourceId;
        uint32_t textureHandle;
        uint32_t width;
        uint32_t height;
    };

    struct RGBA
    {
        RGBA(uint8_t r, uint8_t g, uint8_t b,
             uint8_t a)
             : r(r), g(g), b(b), a(a)
        {}

        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

    struct Vertex
    {
        glm::vec3 vertex;
        RGBA color;
        glm::vec2 uv;
    };

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
        uint32_t shaderHandle;
        uint32_t instances;
    };

    struct Dynamic
    {
        uint32_t vbo;
        uint32_t vao;
        uint32_t ebo;
        uint32_t shaderId;
    };
};