#pragma once

#include <cstdint>
#include <vector>

#include "External/include/glm/glm.hpp"
#include "External/include/entt/entt.hpp"

#include "Engine/include/Global/glPortableHeaders.hpp"

#include "Engine/include/Rendering/ShaderManager.hpp"

#include "Engine/include/Global/Components.hpp"
#include "Engine/include/Collision/CollisionComponents.hpp"
#include "Engine/include/Rendering/BaseRender.hpp"
#include "Engine/include/Rendering/Renderable.hpp"
#include "Engine/include/Rendering/RenderingComponents.hpp"

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