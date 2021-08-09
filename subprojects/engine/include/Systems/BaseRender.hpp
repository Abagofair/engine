#pragma once

#include <entt/entt.hpp>

class BaseRender
{
public:
    virtual void Draw(entt::registry registry) = 0;
};