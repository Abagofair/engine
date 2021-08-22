#pragma once

#include <cstdint>

#include <glm/glm.hpp>

#include <entt/entt.hpp>

#include <glPortableHeaders.hpp>

#include <ShaderManager.hpp>

#include <Components.hpp>

#include <Systems/BaseRender.hpp>

#include <Renderer/Renderable.hpp>

class SpriteRender : public BaseRender
{
public:
    SpriteRender(
        unsigned int width,
        unsigned int height,
        ShaderManager& shaderManager
    );

    /**
     * Setup gl buffers for instanced quad rendering
     * */
    void SetupBuffers(uint32_t amount);
    void Draw(entt::registry &registry);

    unsigned int renderWidth;
    unsigned int renderHeight;

    glm::mat4 viewMatrix;
private:
    ShaderManager& _shaderManager;
};