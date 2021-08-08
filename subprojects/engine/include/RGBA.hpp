#pragma once

#include <DLLEXPORT.hpp>

#include <glm/glm.hpp>

class DLLEXPORT RGBA
{
public:
    RGBA(float x, float y, float z, float a)
        : RgbaVec(glm::vec4(x, y, z, a))
        {}
    
    RGBA(glm::vec4 rgba)
        : RgbaVec(rgba)
        {}

    glm::vec4 RgbaVec = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
};