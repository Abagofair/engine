#include <Engine/Rendering/SpriteRender.hpp>

namespace Engine::Rendering
{
    SpriteRender::SpriteRender(
        entt::registry& registry,
        ShaderManager& shaderManager,
        unsigned int width,
        unsigned int height) 
        : BaseRender(registry, width, height), _shaderManager(shaderManager)
    {
        viewMatrix = glm::ortho<float>(0.0f, (float)width, (float)height, 0.0f, 0.0f, 1.0f);
    }


    //Do copy constructor
    //Do move constructor / operator

    void SpriteRender::Draw()
    {
        auto dynamicRenderablesView = _registry.view<
            const Renderable::Dynamic,
            const Global::Components::TransformComponent>();

        //include multiple textures at shader initialization to the shader so all we have to do is pass in the textureid
        //

        //spriteShader.UseWithOrtho(viewMatrix);
        //glUseProgram(shaderId);
        auto& dynamicShader = _shaderManager.GetShader(Rendering::DYNAMIC_SHADER_NAME);

        for (auto entity : dynamicRenderablesView)
        {
            auto renderable = dynamicRenderablesView.get<const Renderable::Dynamic>(entity);
            auto transform = dynamicRenderablesView.get<const Global::Components::TransformComponent>(entity);

            dynamicShader.Use();
            dynamicShader.SetUniformMat4(transform.transform, "model");
            dynamicShader.SetUniformMat4(viewMatrix, "view");
            glBindVertexArray(renderable.vao);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        //debug view
        auto boundingBoxView = _registry.view<
            Collision::Components::BoundingBoxComponent,
            Global::Components::TransformComponent,
            Renderable::Dynamic>();

        for (auto boundingBox : boundingBoxView)
        {
            auto& boundingBoxComponent = boundingBoxView.get<Collision::Components::BoundingBoxComponent>(boundingBox);
            auto& positionComponent = boundingBoxView.get<Global::Components::TransformComponent>(boundingBox);
            auto& renderable = boundingBoxView.get<Renderable::Dynamic>(boundingBox);

            glm::mat4 t = glm::translate(glm::mat4(1.0f), glm::vec3(positionComponent.position, 0.0f));

            float minX = positionComponent.position.x;
            float minY = positionComponent.position.y;
            float maxX = boundingBoxComponent.width + minX;
            float maxY = boundingBoxComponent.height + minY;
            
            dynamicShader.Use();
            dynamicShader.SetUniformMat4(t, "model");
            dynamicShader.SetUniformMat4(viewMatrix, "view");
            
            glBindVertexArray(renderable.vao);
            glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }

    void SpriteRender::DrawStaticQuads()
    {
        //i dont want to be reliant on EntityType from Game - must be an engine type
        auto staticRenderablesView = _registry.view<
            const Renderable::Static>();

        auto instancedQuadView = _registry.view<
            const Rendering::Components::InstancedQuadComponent>();

        std::vector<uint32_t> ignoredInstances = std::vector<uint32_t>(instancedQuadView.size());
        for (auto instancedQuadEntity : instancedQuadView)
        {
            auto instancedQuad = instancedQuadView.get<const Rendering::Components::InstancedQuadComponent>(instancedQuadEntity);
            if (instancedQuad.ignore)
            {
                ignoredInstances.push_back(1);
            }
            else
            {
                ignoredInstances.push_back(0);
            }
        }

        auto& shader = _shaderManager.GetShader(Rendering::STATIC_SHADER_NAME);
        //todo: loop?
        for (auto entity : staticRenderablesView)
        {
            auto staticRenderable = staticRenderablesView.get<const Renderable::Static>(entity);

            shader.Use();
            shader.SetUniformMat4(viewMatrix, "view");
            shader.SetUniformBoolArray(&ignoredInstances[0], 512, "staticBlocks");
            glBindVertexArray(staticRenderable.vao);
            glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, staticRenderable.instances);
            glBindVertexArray(0);
        }
    }
};