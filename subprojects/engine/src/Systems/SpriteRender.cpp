#include <SpriteRender.hpp>

SpriteRender::SpriteRender()
{

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
        
    });
}