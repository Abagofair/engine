#pragma once

#include <cstdint>

#include <External/entt/entt.hpp>

namespace Engine::Rendering
{
    class BaseRender
    {
    public:
        BaseRender(
            entt::registry& registry,
            uint32_t width,
            uint32_t height)
            : _registry(registry)
        {}

        virtual ~BaseRender() {}
        virtual void Draw() = 0;

    protected:
        entt::registry& _registry;
    };
};