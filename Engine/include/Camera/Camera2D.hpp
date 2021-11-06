#pragma once

#include <cstdint>

#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

namespace Engine::Camera
{
    struct Camera2D
    {
        glm::mat4 viewMatrix;
        uint32_t width;
        uint32_t height;

        Camera2D(uint32_t width, uint32_t height)
                : width(width),
                  height(height),
                  viewMatrix(glm::ortho<float>(0.0f, (float) width, (float) height, 0.0f, 0.0f, 1.0f))
        {}

        Camera2D(const Camera2D &) = default;
    };
};