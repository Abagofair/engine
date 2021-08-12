#pragma once

#include <glm/glm.hpp>

#include <glPortableHeaders.hpp>

#include <Components/Position2D.hpp>
#include <Components/Rotation2D.hpp>
#include <Components/Scale2D.hpp>
#include <Components/Texture2D.hpp>
#include <Components/SpriteShader.hpp>

#include <Systems/BaseRender.hpp>

class SpriteRender : public BaseRender
{
    public:
        SpriteRender(
            unsigned int width,
            unsigned int height
        );
        ~SpriteRender();

        void Draw(entt::registry registry);

        unsigned int renderWidth;
        unsigned int renderHeight;

        glm::mat4 viewMatrix;
};