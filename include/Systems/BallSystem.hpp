#pragma once

#include <entt/entt.hpp>

#include <Components.hpp>

#include <iostream>

class BallSystem 
{
public:
    BallSystem(entt::registry& registry);

    void Update();

private:
    entt::registry& _registry;
};