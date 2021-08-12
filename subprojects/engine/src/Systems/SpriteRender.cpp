#include <SpriteRender.hpp>

SpriteRender::SpriteRender(
    unsigned int width,
    unsigned int height
) : renderWidth(width), renderHeight(height)
{
    viewMatrix = glm::ortho<float>(0, (float)width, (float)height, 0, -1.0f, 1.0f);
}

SpriteRender::~SpriteRender()
{

}

void SpriteRender::Draw(entt::registry registry)
{
    auto view = registry.view<
        const Position2D, 
        const Rotation2D,
        const Scale2D,
        const Texture2D,
        const SpriteShader>();

    std::for_each(view.begin(), view.end(), [&view](auto entity) {
        Position2D &position2d = view.get<Position2D>(entity);
        Rotation2D &rotation2d = view.get<Position2D>(entity);
        Scale2D &scale2d = view.get<Position2D>(entity);
        Texture2D &texture2d = view.get<Position2D>(entity);
        SpriteShader &spriteShader = view.get<Position2D>(entity);

        //how to cache transform?


        spriteShader.UseWithOrtho(viewMatrix);

        glBindVertexArray(_glVAOId);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    });
}