#pragma once

#include <cstdint>
#include <vector>

#include "glm/glm.hpp"
#include "entt/entt.hpp"

#include "Global/glPortableHeaders.hpp"

#include "Resources/ResourceHandler.hpp"

#include "Global/Components.hpp"
#include "Collision/CollisionComponents.hpp"
#include "Rendering/Renderable.hpp"
#include "Rendering/RenderingComponents.hpp"

namespace Engine::Rendering
{
    void DrawDynamics(const entt::registry& registry,
                      glm::mat4 viewMatrix);

    void DrawStatics(const entt::registry& registry,
                     glm::mat4 viewMatrix);
};