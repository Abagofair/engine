#pragma once

#include <cstdint>

#include <glm/glm.hpp>

#include <entt/entt.hpp>

#include <glPortableHeaders.hpp>

#include <Components.hpp>
#include <Components/Texture2D.hpp>
#include <Components/SpriteShader.hpp>

#include <Systems/BaseRender.hpp>

#include <Renderer/Quad.hpp>

class SpriteRender : public BaseRender
{
    public:
        SpriteRender(
            unsigned int width,
            unsigned int height
        );
        ~SpriteRender();

        /**
         * Setup gl buffers for instanced quad rendering
         * */
        void SetupBuffers();
        void Draw(entt::registry &registry);

        unsigned int renderWidth;
        unsigned int renderHeight;

        glm::mat4 viewMatrix;

    private:
        uint32_t quadMax;

        uint32_t vbo;
        uint32_t vao;
        uint32_t ebo;
};