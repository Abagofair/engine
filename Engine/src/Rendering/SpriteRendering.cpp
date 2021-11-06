#include "Rendering/SpriteRendering.hpp"

namespace Engine::Rendering
{
    void Rendering::DrawDynamics(const entt::registry &registry, glm::mat4 viewMatrix)
    {
        auto dynamicRenderablesView = registry.view<
                const Engine::Rendering::Components::RenderableComponent,
                const Global::Components::TransformComponent>();

        //include multiple textures at shader initialization to the shader so all we have to do is pass in the textureid

        //spriteShader.UseWithOrtho(viewMatrix);
        //glUseProgram(shaderHandle);
        auto& dynamicShader = Resources::GetShader(Resources::DYNAMIC_SHADER_NAME);

        dynamicShader.Use();

        for (auto entity : dynamicRenderablesView)
        {
            auto renderable = dynamicRenderablesView.get<const Engine::Rendering::Components::RenderableComponent>(entity);
            auto transform = dynamicRenderablesView.get<const Global::Components::TransformComponent>(entity);

            dynamicShader.SetUniformMat4(transform.transform, "model");
            dynamicShader.SetUniformMat4(viewMatrix, "view");

            glBindTexture(GL_TEXTURE_2D, renderable.textureHandle);
            glBindVertexArray(renderable.vao);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        //debug view
        /*auto boundingBoxView = _registry.view<
            Collision::Components::BoundingBoxComponent,
            Global::Components::TransformComponent,
            Engine::Rendering::Components::DebugRenderableComponent>();

        auto& debugShader = _shaderManager.GetShader(Rendering::ShaderManager::DEBUG_SHADER_NAME);

        for (auto boundingBox : boundingBoxView)
        {
            auto& boundingBoxComponent = boundingBoxView.get<Collision::Components::BoundingBoxComponent>(boundingBox);
            auto& positionComponent = boundingBoxView.get<Global::Components::TransformComponent>(boundingBox);
            auto& renderable = boundingBoxView.get<Engine::Rendering::Components::DebugRenderableComponent>(boundingBox);

            glm::mat4 t = glm::translate(glm::mat4(1.0f), glm::vec3(positionComponent.position, 0.0f));

            float minX = positionComponent.position.x;
            float minY = positionComponent.position.y;
            float maxX = boundingBoxComponent.width + minX;
            float maxY = boundingBoxComponent.height + minY;

            debugShader.Use();
            debugShader.SetUniformMat4(t, "model");
            debugShader.SetUniformMat4(viewMatrix, "view");

            glBindVertexArray(renderable.vao);
            glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }*/
    }

    void Rendering::DrawStatics(const entt::registry &registry, glm::mat4 viewMatrix)
    {
        auto staticRenderablesView = registry.view<
                const Engine::Rendering::Components::StaticRenderableComponent>();

        auto instancedQuadView = registry.view<
                const Rendering::Components::InstancedQuadComponent>();

        std::vector<unsigned int> ignoredInstances = std::vector<unsigned int>(instancedQuadView.size());
        int count = instancedQuadView.size() - 1;
        for (auto instancedQuadEntity : instancedQuadView)
        {
            auto instancedQuad = instancedQuadView.get<const Rendering::Components::InstancedQuadComponent>(instancedQuadEntity);
            if (instancedQuad.ignore)
            {
                ignoredInstances[count] = 0;
            }
            else
            {
                ignoredInstances[count] = 1;
            }
            count -= 1;
        }

        auto& shader = Resources::GetShader(Resources::STATIC_SHADER_NAME);
        //todo: loop?
        for (auto entity : staticRenderablesView)
        {
            auto staticRenderable = staticRenderablesView.get<const Engine::Rendering::Components::StaticRenderableComponent>(entity);

            shader.Use();
            shader.SetUniformMat4(viewMatrix, "view");
            shader.SetUniformBoolArray(ignoredInstances.data(), ignoredInstances.size(), "staticBlocks");
            glBindVertexArray(staticRenderable.vao);
            glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, staticRenderable.instances);
            glBindVertexArray(0);
        }
    }
};