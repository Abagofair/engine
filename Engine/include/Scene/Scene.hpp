#pragma once

#include "Camera/Camera2D.hpp"

namespace Engine::Scene
{
    struct Scene
    {
        Scene() = default;
        virtual ~Scene() = default;

        virtual void Initialize() = 0;
        virtual void CheckSceneState() = 0;

        Camera::Camera2D *camera = nullptr;
    };
};