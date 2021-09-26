#pragma once

#include <External/entt/entt.hpp>

namespace Engine::Scene
{
    class Scene
    {
    public:
        Scene();
        ~Scene();

        void Initialize();
        void Update();
        void Draw();
    protected:
        //WorldSystems
        //  AISystem
        //  PhysicSystem
        //  CollisionSystem
        //  GoalStateSystem
        //RenderSystems
    };
};