#pragma once

namespace Engine::Collision::Components
{
    struct BoundingBoxComponent 
    {
        float width;
        float height;
        bool contains; //todo: should be result of method?
        bool ignoreCollisions;

        BoundingBoxComponent() = default;
        BoundingBoxComponent(const BoundingBoxComponent&) = default;
        BoundingBoxComponent(float width, float height, bool contains, bool ignoreCollisions)
            : width(width), height(height), contains(contains), ignoreCollisions(ignoreCollisions)
            {}
    };
};