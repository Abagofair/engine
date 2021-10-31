#pragma once

#include <iostream>

#include "entt/entt.hpp"

#include "Global/Time/Time.hpp"
#include "Global/Components.hpp"

#include "Physics/PhysicsComponents.hpp"

namespace Engine::Physics
{
    class IntegrationSystem
    {
    public:
        IntegrationSystem(entt::registry& registry);

        void Integrate(Global::Time::Time time);

    private:
        entt::registry& _registry;
    };
};