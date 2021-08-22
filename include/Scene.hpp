#pragma once

#include <entt/entt.hpp>

class Scene
{
public:
    Scene();
    ~Scene();

    entt::registry registry;

    void Initialize();
    void Update();
    void Draw();
private:
    //WorldSystems
    //  AISystem
    //  PhysicSystem
    //  CollisionSystem
    //  GoalStateSystem
    //RenderSystems
};