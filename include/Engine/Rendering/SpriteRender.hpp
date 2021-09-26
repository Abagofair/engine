#pragma once

#include <cstdint>
#include <vector>

#include <External/glm/glm.hpp>
#include <External/entt/entt.hpp>

#include <Engine/Global/glPortableHeaders.hpp>

#include <Engine/Rendering/ShaderManager.hpp>

#include <Engine/Global/Components.hpp>
#include <Engine/Collision/CollisionComponents.hpp>
#include <Engine/Rendering/BaseRender.hpp>
#include <Engine/Rendering/Renderable.hpp>
#include <Engine/Rendering/RenderingComponents.hpp>

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