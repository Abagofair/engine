#pragma once

#include <cstdint>

namespace Engine::Rendering::Components
{
    enum Primitive
    {
        Quad
    };

    struct InstancedQuadComponent
    {
        bool ignore;

        InstancedQuadComponent() = default;
        InstancedQuadComponent(const InstancedQuadComponent&) = default;
        InstancedQuadComponent(bool ignore)
            : ignore(ignore)
            {}
    };

    struct RenderableComponent
    {
        uint32_t vbo;
        uint32_t vao;
        uint32_t ebo;
        uint32_t shaderId;
        Primitive primitive;

        RenderableComponent() = default;
        RenderableComponent(const RenderableComponent&) = default;
        RenderableComponent(uint32_t vbo, uint32_t vao, uint32_t ebo, uint32_t shaderId, Primitive primitive)
            : vbo(vbo), vao(vao), ebo(ebo), shaderId(shaderId), primitive(primitive)
            {}
    };

    struct StaticRenderableComponent : public RenderableComponent
    {
        uint32_t instances;

        StaticRenderableComponent() = default;
        StaticRenderableComponent(const StaticRenderableComponent&) = default;
        StaticRenderableComponent(uint32_t vbo, uint32_t vao, uint32_t ebo, uint32_t shaderId, Primitive primitive, uint32_t instances)
            : RenderableComponent(vbo, vao, ebo, shaderId, primitive), instances(instances)
            {}
    };
};