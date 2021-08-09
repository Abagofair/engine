#pragma once

#include <Components/Position2D.hpp>
#include <Components/Rotation2D.hpp>
#include <Components/Scale2D.hpp>
#include <Components/Texture2D.hpp>
#include <Components/SpriteShader.hpp>

#include <Systems/BaseRender.hpp>

class SpriteRender : public BaseRender
{
    public:
        SpriteRender();
        ~SpriteRender();

        void Draw(entt::registry registry);
};