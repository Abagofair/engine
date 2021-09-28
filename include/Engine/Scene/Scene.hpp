#pragma once

#include <External/entt/entt.hpp>

namespace Engine::Scene
{
    class Scene
    {
    public:
        Scene() = default;
        virtual ~Scene() = default;

        virtual void Initialize() = 0;
    };
};