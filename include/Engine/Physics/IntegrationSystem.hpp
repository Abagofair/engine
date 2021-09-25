#pragma once

#include <iostream>

#include <External/entt/entt.hpp>

#include <Engine/Global/Time/Time.hpp>
#include <Engine/Global/Components.hpp>

#include <Engine/Physics/PhysicsComponents.hpp>

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