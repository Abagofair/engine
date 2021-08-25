#pragma once

#include <entt/entt.hpp>
#include <Time.hpp>

#include <Components.hpp>

class IntegrationSystem
{
public:
    IntegrationSystem(entt::registry& registry);

    void Integrate(InternalTime::Time time);

private:
    entt::registry& registry;
};