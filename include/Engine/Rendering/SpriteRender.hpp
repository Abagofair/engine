#pragma once

#include <cstdint>

#include <External/glm/glm.hpp>
#include <External/entt/entt.hpp>

#include <Engine/Global/glPortableHeaders.hpp>

#include <Engine/Rendering/ShaderManager.hpp>

#include <Engine/Global/Components.hpp>
#include <Engine/Collision/CollisionComponents.hpp>
#include <Engine/Rendering/BaseRender.hpp>
#include <Engine/Rendering/Renderable.hpp>

namespace Engine::Rendering
{
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
};