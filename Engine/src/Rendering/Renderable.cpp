#include "Renderable.hpp"

namespace Engine::Rendering
{
    std::array<Rendering::Structures::Vertex, 4> CreateVertices(uint32_t width, uint32_t height, std::array<Rendering::Structures::RGBA, 4> colors)
    {
        Rendering::Structures::Vertex quad1
        {
            .vertex = glm::vec3(0.0f, 0.0f, 0.0f),
            .color = colors[0],
            .uv = glm::vec2(0.0f, 0.0f)
        };

        Rendering::Structures::Vertex quad2
        {
            .vertex = glm::vec3((float)width, 0.0f, 0.0f),
            .color = colors[1],
            .uv = glm::vec2(1.0f, 0.0f)
        };

        Rendering::Structures::Vertex quad3
        {
            .vertex = glm::vec3((float)width, (float)height, 0.0f),
            .color = colors[2],
            .uv = glm::vec2(1.0f, 1.0f),
        };

        Rendering::Structures::Vertex quad4
        {
            .vertex = glm::vec3(0.0f, (float)height, 0.0f),
            .color = colors[3],
            .uv = glm::vec2(0.0f, 1.0f)
        };

        std::array<Rendering::Structures::Vertex, 4> vertices
        {
            quad1, quad2, quad3, quad4
        };

        return vertices;
    }

    Rendering::Components::RenderableComponent SetupDynamic(uint32_t textureHandle, uint32_t shaderHandle, uint32_t width, uint32_t height)
    {
        Rendering::Components::RenderableComponent renderable;
        renderable.shaderHandle = shaderHandle;
        renderable.textureHandle = textureHandle;
        renderable.primitive = Rendering::Components::Primitive::Quad;

        std::array<Rendering::Structures::RGBA, 4> colors =
         {
             Rendering::Structures::RGBA(255, 255, 255, 0),
             Rendering::Structures::RGBA(255, 255, 255, 0),
             Rendering::Structures::RGBA(255, 255, 255, 0),
             Rendering::Structures::RGBA(255, 255, 255, 0),
         };

        std::array<Rendering::Structures::Vertex, 4> vertices = CreateVertices(width, height, colors);

        constexpr uint32_t indexCount = 6;
        uint32_t quadIndices[indexCount] =
        {
            0, 1, 3,
            1, 2, 3
        };

        GLHelper::VboVaoEboPosColorTex(
                vertices,
                indexCount * sizeof(uint32_t),
                quadIndices,
                3,
                4,
                2,
                renderable.vbo,
                renderable.vao,
                renderable.ebo);

        return renderable;
    }

    Rendering::Components::DebugRenderableComponent SetupDebug(uint32_t shaderHandle, uint32_t width, uint32_t height)
    {
        Rendering::Components::DebugRenderableComponent renderable;
        renderable.shaderHandle = shaderHandle;
        renderable.primitive = Rendering::Components::Primitive::Quad;

        std::array<Rendering::Structures::RGBA, 4> colors =
        {
                Rendering::Structures::RGBA(0, 255, 0, 255),
                Rendering::Structures::RGBA(0, 255, 0, 255),
                Rendering::Structures::RGBA(0, 255, 0, 255),
                Rendering::Structures::RGBA(0, 255, 0, 255),
        };

        std::array<Rendering::Structures::Vertex, 4> vertices = CreateVertices(width, height, colors);

        constexpr uint32_t indexCount = 6;
        uint32_t quadIndices[indexCount] =
        {
            0, 1, 3,
            1, 2, 3
        };

        GLHelper::VboVaoEboPosColorTex(
                vertices,
                indexCount * sizeof(uint32_t),
                quadIndices,
                3,
                4,
                2,
                renderable.vbo,
                renderable.vao,
                renderable.ebo);

        return renderable;
    }

    Rendering::Components::StaticRenderableComponent SetupStatic(uint32_t textureHandle, uint32_t shaderHandle, std::vector<glm::mat4> transforms, uint32_t width, uint32_t height)
    {
        Rendering::Components::StaticRenderableComponent renderable;

        std::array<Rendering::Structures::RGBA, 4> colors =
        {
                Rendering::Structures::RGBA(126, 126, 126, 255),
                Rendering::Structures::RGBA(126, 126, 126, 255),
                Rendering::Structures::RGBA(126, 126, 126, 255),
                Rendering::Structures::RGBA(126, 126, 126, 255),
        };

        std::array<Rendering::Structures::Vertex, 4> vertices = CreateVertices(width, height, colors);

        constexpr uint32_t indexCount = 6;
        uint32_t quadIndices[indexCount] =
        {
            0, 1, 3,
            1, 2, 3
        };

        GLHelper::VboVaoEboPosColorTex(
                vertices,
                indexCount * sizeof(uint32_t),
                quadIndices,
                3,
                4,
                2,
                renderable.vbo,
                renderable.vao,
                renderable.ebo);

        renderable.shaderHandle = shaderHandle;
        renderable.textureHandle = textureHandle;
        renderable.instances = transforms.size();

        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(glm::mat4), &transforms[0], GL_STATIC_DRAW);

        glBindVertexArray(renderable.vao);

        // set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);

        return renderable;
    }
};