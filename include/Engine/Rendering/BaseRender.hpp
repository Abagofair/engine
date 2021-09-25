#pragma once

#include <External/entt/entt.hpp>

namespace Engine::Rendering
{
    class BaseRender
    {
    public:
        virtual ~BaseRender() {}
        virtual void Draw(entt::registry &registry) = 0;
    };
};