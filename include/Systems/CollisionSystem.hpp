#pragma once

#include <entt/entt.hpp>

#include <Window.hpp>
#include <Components.hpp>

class CollisionSystem
{
public:
    CollisionSystem(entt::registry& registry,
        Window& Window);

    void ResolveVelocities();

private:
    entt::registry& _registry;
    Window& _window;
};