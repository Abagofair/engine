#pragma once

#include <DLLEXPORT.hpp>

#include <glm/glm.hpp>

#include <Texture2D.hpp>

class DLLEXPORT Sprite
{
public:
    Sprite();
    ~Sprite();

    Texture2D texture;

    glm::vec2 position;
    float rotation;
    glm::vec2 scale;
}