#pragma once

#include <iostream>

#include "External/include/entt/entt.hpp"

#include "Engine/include/Global/Time/Time.hpp"
#include "Engine/include/Global/Components.hpp"

#include "Engine/include/Physics/PhysicsComponents.hpp"

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