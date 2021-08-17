#include <Systems/SpriteRender.hpp>

SpriteRender::SpriteRender(
    unsigned int width,
    unsigned int height
) : renderWidth(width), renderHeight(height)
{
    viewMatrix = glm::ortho<float>(0, (float)width, (float)height, 0, -1.0f, 1.0f);
}


//Do copy constructor
//Do move constructor / operator

void SpriteRender::Draw(entt::registry &registry)
{
    auto staticRenderablesView = registry.view<const Static>();
    auto dynamicRenderablesView = registry.view<const Dynamic>();

    uint32_t instanceCount = 0;

    //TODO: Should probably find a way to get the actual shader program
    uint32_t shaderId = 0;

    //include multiple textures at shader initialization to the shader so all we have to do is pass in the textureid
    //

    //spriteShader.UseWithOrtho(viewMatrix);
    glUseProgram(shaderId);
    for (auto entity : staticRenderablesView)
    {
        auto staticRenderable = staticRenderablesView.get<const Dynamic>(entity);

        glBindVertexArray(staticRenderable.vao);
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, instanceCount);
        glBindVertexArray(0);
    }

    glUseProgram(shaderId);
    for (auto entity : dynamicRenderablesView)
    {
        auto dynamicRenderable = dynamicRenderablesView.get<const Dynamic>(entity);

        glBindVertexArray(dynamicRenderable.vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}