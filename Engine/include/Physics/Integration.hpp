#pragma once

#include "entt/entt.hpp"

#include "Global/Time/Time.hpp"
#include "Global/Components.hpp"
#include "Physics/PhysicsComponents.hpp"

namespace Engine::Physics
{
    void Integrate(entt::registry &registry, Global::Time::Time time);
};