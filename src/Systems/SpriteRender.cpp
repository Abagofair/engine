#include <Systems/SpriteRender.hpp>

SpriteRender::SpriteRender(
    unsigned int width,
    unsigned int height,
    ShaderManager& shaderManager
) : renderWidth(width), renderHeight(height), _shaderManager(shaderManager)
{
    viewMatrix = glm::ortho<float>(0.0f, (float)width, (float)height, 0.0f, 0.0f, 1.0f);
}


//Do copy constructor
//Do move constructor / operator

void SpriteRender::Draw(entt::registry &registry)
{
    auto staticRenderablesView = registry.view<const Renderables::Static>();
    auto dynamicRenderablesView = registry.view<
        const Renderables::Dynamic,
        const Components::TransformComponent>();

    //include multiple textures at shader initialization to the shader so all we have to do is pass in the textureid
    //

    //spriteShader.UseWithOrtho(viewMatrix);
    //glUseProgram(shaderId);
    for (auto entity : dynamicRenderablesView)
    {
        auto renderable = dynamicRenderablesView.get<const Renderables::Dynamic>(entity);
        auto transform = dynamicRenderablesView.get<const Components::TransformComponent>(entity);

        auto& shader = _shaderManager.GetShader(renderable.shaderId);
        shader.Use();
        shader.SetUniformMat4(transform.transform, "model");
        shader.SetUniformMat4(viewMatrix, "view");
        glBindVertexArray(renderable.vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    
    unsigned int data[512];
	for (int i = 0; i < 512; ++i)
	{
		data[i] = 1;
	}

    for (auto entity : staticRenderablesView)
    {
        auto staticRenderable = staticRenderablesView.get<const Renderables::Static>(entity);

        auto& shader = _shaderManager.GetShader(staticRenderable.shaderId);
        shader.Use();
        shader.SetUniformMat4(viewMatrix, "view");
        shader.SetUniformBoolArray(data, 512, "staticBlocks");
        glBindVertexArray(staticRenderable.vao);
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, staticRenderable.instances);
        glBindVertexArray(0);
    }

    //debug view
    auto boundingBoxView = registry.view<
        Components::BoundingBoxComponent,
        Components::SpriteComponent,
        Renderables::Dynamic>();

    for (auto boundingBox : boundingBoxView)
    {
        auto& boundingBoxComponent = boundingBoxView.get<Components::BoundingBoxComponent>(boundingBox);
        auto& positionComponent = boundingBoxView.get<Components::SpriteComponent>(boundingBox);
        auto& renderable = boundingBoxView.get<Renderables::Dynamic>(boundingBox);

		glm::mat4 t = glm::translate(glm::mat4(1.0f), glm::vec3(positionComponent.position, 0.0f));

        float minX = positionComponent.position.x;
        float minY = positionComponent.position.y;
        float maxX = boundingBoxComponent.width + minX;
        float maxY = boundingBoxComponent.height + minY;
        
        auto& shader = _shaderManager.GetShader(renderable.shaderId);
        shader.Use();
        shader.SetUniformMat4(t, "model");
        shader.SetUniformMat4(viewMatrix, "view");
        
        glBindVertexArray(renderable.vao);
        glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}