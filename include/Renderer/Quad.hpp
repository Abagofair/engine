#pragma once

#include <cstdint>

struct Quad
{
    float vertices[12] = 
    {
        -0.05f,  0.05f,  0.0f,
         0.05f, -0.05f,  0.0f,
        -0.05f, -0.05f,  0.0f,
         0.05f,  0.05f,  0.0f
    };

    float indices[6] =
    {
        2, 0, 3,
        3, 1, 2
    };

    uint32_t vbo;
    uint32_t vao;
    uint32_t ebo;
};