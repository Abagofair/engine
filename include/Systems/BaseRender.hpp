#pragma once

#include <entt/entt.hpp>

class BaseRender
{
public:
    virtual ~BaseRender() {}
    virtual void Draw(entt::registry &registry) = 0;
};