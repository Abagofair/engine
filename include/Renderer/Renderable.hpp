#pragma once

#include <cstdint>

#include <vector>

#include <glm/glm.hpp>

#include <glPortableHeaders.hpp>

namespace Renderables
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
    Dynamic SetupDynamic(uint32_t shaderId, uint32_t width, uint32_t height);
    Static SetupStatic(uint32_t shaderId, std::vector<glm::mat4> transforms, uint32_t width, uint32_t height);
};