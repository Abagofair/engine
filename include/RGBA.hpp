#pragma once

#include <glm/vec4.hpp>

class RGBA
{
public:
    RGBA(float x, float y, float z, float a)
        : RgbaVec(glm::vec4(x, y, z, a))
        {}
    
    RGBA(glm::vec4 rgba)
        : RgbaVec(rgba)
        {}

    RGBA()
        : RgbaVec(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f))
        {}

    glm::vec4 RgbaVec;
};