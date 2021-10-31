#pragma once

#include <cstdint>
#include <vector>

#include "glm/glm.hpp"
#include "entt/entt.hpp"

#include "Global/glPortableHeaders.hpp"

#include "Rendering/ShaderManager.hpp"

#include "Global/Components.hpp"
#include "Collision/CollisionComponents.hpp"
#include "Rendering/BaseRender.hpp"
#include "Rendering/Renderable.hpp"
#include "Rendering/RenderingComponents.hpp"

namespace Engine::Rendering
{
    class SpriteRender : public BaseRender
    {
    public:
        SpriteRender(
            entt::registry& registry,
            ShaderManager& shaderManager,
            unsigned int width,
            unsigned int height
        );

        /**
         * Setup gl buffers for instanced quad rendering
         * */
        void SetupBuffers(uint32_t amount);
        
        void Draw();
        void DrawStaticQuads();

        unsigned int renderWidth;
        unsigned int renderHeight;

        glm::mat4 viewMatrix;
    private:
        ShaderManager& _shaderManager;
    };
};